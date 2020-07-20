#include <boost/program_options.hpp>
#include <GeneratorException.hpp>
#include <PlainTextGenerator.hpp>
#include <HtmlGenerator.hpp>
#include <Parser.hpp>
#include <optional>
#include <iostream>
#include <vector>
#include <string>

using namespace std::literals::string_literals;
namespace po = boost::program_options;
namespace fs = boost::filesystem;

struct [[maybe_unused]] ConflictAdder {
  const po::variables_map &vm;

  template<typename... Args>
  auto operator()(const Args &...opts) const -> auto {
    const auto conflict = (... + (vm.count(opts) && !vm[opts].defaulted())) >= 2;
    if (conflict) {
      throw std::logic_error(
          "Conflicting arguments detected: Only zero or one of ["s + (... + (opts + ", "s)) + "] is allowed."s
      );
    }
    return *this;
  }
};

struct [[maybe_unused]] DependencyAdder {
  const po::variables_map &vm;

  template<typename... Args>
  auto operator()(
      const char *baseOption,
      const Args &...requiredOptions
  ) const -> auto {
    const auto base = vm.count(baseOption) && !vm[baseOption].defaulted();
    const auto allRequired = (... && (vm.count(requiredOptions) != 0 && !vm[requiredOptions].defaulted()));
    if (base && !allRequired)
      throw std::logic_error(
          "Option '"s + baseOption + "' requires options ["s + (... + (requiredOptions + ", "s)) + "]."s
      );
    return *this;
  }
};

int main(int argc, char **argv) {
  try {
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "print usage message")
        (
            "output,o",
            po::value<fs::path>()->required()->default_value("stdout"),
            "pathname for output (default is stdout)"
        )
        ("table,t", po::value<fs::path>()->required(), "full pathname of translation-table")
        ("input,i", po::value<std::vector<fs::path>>()->multitoken()->required(), "file(s) to handle")
        ("html,H", po::bool_switch()->default_value(false), "set output-type to html")
        ("xml,X", po::bool_switch()->default_value(false), "set output-type to xml")
        ("pdf,P", po::bool_switch()->default_value(false), "set output-type to xml")
        (
            "filter,f",
            po::value<std::vector<std::string>>()->multitoken()->default_value({}, ""),
            "filter output for a style-name(s)"
        )
        ("sort,s", po::value<std::string>()->default_value(""), "sort output for a field");

    po::variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);

    if (vm.count("help")) {
      std::cout << desc << "\n";
      return 0;
    }

    ConflictAdder{vm}
        ("html", "xml", "pdf");

    DependencyAdder{vm}
        ("html", "input", "table")
        ("xml", "input", "table")
        ("pdf", "input", "table");

    const Parser parser{vm["table"].as<fs::path>(), vm["filter"].as<std::vector<std::string>>()};
    const auto elements = parser.generate(
        vm["input"].as<std::vector<fs::path>>(),
        vm["sort"].as<std::string>().empty() ? std::nullopt : std::optional(vm["sort"].as<std::string>())
    );

    std::string output;
    if (vm["html"].as<bool>()) output = HtmlGenerator(elements).write();
    else output = PlainTextGenerator(elements).write();

    if (vm["output"].defaulted()) {
      std::cout << output << '\n';
    } else {
      std::ofstream f{vm["output"].as<boost::filesystem::path>().string()};
      if (f.is_open()) {
        f << output;
        f.close();
      } else {
        throw GeneratorException("Could not write to file: " + vm["output"].as<boost::filesystem::path>().string());
      }
    }
  }
  catch (std::exception &e) {
    std::cerr << e.what() << "\n";
    return -1;
  }
  return 0;
}