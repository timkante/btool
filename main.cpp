#include <iostream>
#include <boost/program_options.hpp>
#include <vector>
#include <Parser.hpp>
#include <fstream>
#include <BibElement.hpp>
#include <HtmlGenerator.hpp>

namespace po = boost::program_options;

void conflicting_options(
    const po::variables_map &vm,
    const char *opt1, const char *opt2
) {
  if (vm.count(opt1) && !vm[opt1].defaulted()
      && vm.count(opt2) && !vm[opt2].defaulted())
    throw std::logic_error(
        std::string("Conflicting options '")
            + opt1 + "' and '" + opt2 + "'."
    );
}

/* Function used to check that of 'for_what' is specified, then
   'required_option' is specified too. */
void option_dependency(
    const po::variables_map &vm,
    const char *for_what,
    const char *required_option
) {
  if (vm.count(for_what) && !vm[for_what].defaulted())
    if (vm.count(required_option) == 0 || vm[required_option].defaulted())
      throw std::logic_error(std::string("Option '") + for_what
                                 + "' requires option '" + required_option + "'.");
}

int main(int argc, char **argv) {
  try {
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "print usage message")
        ("output,o", po::value<boost::filesystem::path>()->required(), "pathname for output")
        ("table,t", po::value<boost::filesystem::path>()->required(), "full pathname of translation-table")
        ("input,i", po::value<std::vector<boost::filesystem::path>>()->multitoken(), "file(s) to handle")
        ("html,H", po::bool_switch()->default_value(false), "set output-type to html")
        ("xml,X", po::bool_switch()->default_value(false), "set output-type to xml")
        ("pdf,P", po::bool_switch()->default_value(false), "set output-type to xml")
        ("console,C", po::bool_switch()->default_value(false), "set output-type to plain-text (printed to stdout)")
        ("filter,f", po::value<std::vector<std::string>>()->multitoken(), "filter output for a style-name(s)")
        ("sort,s", po::value<std::string>()->default_value(""), "sort output for a field");

    po::variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);

    if (vm.count("help")) {
      std::cout << desc << "\n";
      return 0;
    }

    conflicting_options(vm, "html", "xml");
    conflicting_options(vm, "html", "pdf");
    conflicting_options(vm, "xml", "pdf");

    option_dependency(vm, "html", "output");
    option_dependency(vm, "xml", "output");
    option_dependency(vm, "pdf", "output");
    option_dependency(vm, "html", "table");
    option_dependency(vm, "xml", "table");
    option_dependency(vm, "pdf", "table");

    const Parser parser{vm["table"].as<boost::filesystem::path>(), vm["filter"].as<std::vector<std::string>>()};
    std::vector<BibElement> parsedElements;
    std::for_each(
        std::cbegin(vm["input"].as<std::vector<boost::filesystem::path>>()),
        std::cend(vm["input"].as<std::vector<boost::filesystem::path>>()),
        [&](const boost::filesystem::path &p) {
          const auto elements = parser.generate(p, vm["sort"].as<std::string>());
          parsedElements.insert(std::end(parsedElements), std::cbegin(elements), std::cend(elements));
        }
    );
    std::string output;
    if (vm["html"].as<bool>()) output = HtmlGenerator(parsedElements).write();

    std::ofstream f{vm["output"].as<boost::filesystem::path>().string()};
    if (f.is_open()) {
      f << output;
      f.close();
    } else {
      std::cout << "No Filestream\n";
    }

    std::cout << "html = " << vm["html"].as<bool>() << "\n";
    std::cout << "output to = " << vm["output"].as<boost::filesystem::path>().string() << "\n";
  }
  catch (std::exception &e) {
    std::cerr << e.what() << "\n";
    return -1;
  }
  return 0;
}