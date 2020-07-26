#include <boost/program_options.hpp>
#include <GeneratorException.hpp>
#include <PlainTextGenerator.hpp>
#include <HtmlGenerator.hpp>
#include <XmlGenerator.hpp>
#include <Parser.hpp>
#include <optional>
#include <iostream>
#include <vector>
#include <string>

using namespace std::literals::string_literals;
namespace po = boost::program_options;
namespace fs = boost::filesystem;

/**
 * Handles Conflicts of program-options
 */
struct [[maybe_unused]] Conflicts {
  const po::variables_map &vm; ///< The variables-map, parsed from command line

  /**
   * Checks vm for conflicts
   * @tparam Args interdependent options (const char *) of variable-size
   * @param opts the options
   * @return this to add more conflicts
   * @throws logic_error if any conflicting options occur
   */
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

/**
 * Handles Dependencies of program-options
 */
struct [[maybe_unused]] Dependencies {
  const po::variables_map &vm; ///< The variables-map, parsed from command line

  /**
   * Checks dependencies of program options
   * @tparam Args required options (const char *) of variable-size
   * @param baseOption option that requires one or more other options
   * @param dependencies the required options
   * @return this to add more requirements
   * @throws logic_error if option requirements are not met
   */
  template<typename... Args>
  auto operator()(
      const char *baseOption,
      const Args &...dependencies
  ) const -> auto {
    const auto base = vm.count(baseOption) && !vm[baseOption].defaulted();
    const auto allDependencies = (... && (vm.count(dependencies) != 0 && !vm[dependencies].defaulted()));
    if (base && !allDependencies)
      throw std::logic_error(
          "Option '"s + baseOption + "' requires options ["s + (... + (dependencies + ", "s)) + "]."s
      );
    return *this;
  }
};

/**
 * Handles Dependencies of program-options
 */
struct [[maybe_unused]] Requirements {
  const po::variables_map &vm; ///< The variables-map, parsed from command line

  /**
   * Checks required program options
   * @tparam Args required options (const char *) of variable-size
   * @param requiredOptions the required options
   * @return this to add more requirements
   * @throws logic_error if option requirements are not met
   */
  template<typename... Args>
  auto operator()(
      const Args &...requiredOptions
  ) const -> auto {
    const auto allRequired = (... && (vm.count(requiredOptions) != 0 && !vm[requiredOptions].defaulted()));
    if (!allRequired)
      throw std::logic_error(
          "Options ["s + (... + (requiredOptions + ", "s)) + "] are required for the program to run."s
      );
    return *this;
  }
};

/**
 * Defines CLI and translates program arguments
 * @param argc the number of program arguments
 * @param argv the program arguments
 * @param vm[out] the variables map to store command-line-parameters into
 * @param description[out] the cli description to populate
 */
void parseCommandLine(int argc, char **argv, po::variables_map &vm, po::options_description &description) {
  description.add_options()
      ("help,h", "print usage message")
      (
          "output,o",
          boost::program_options::value<fs::path>()->required()->default_value("stdout"),
          "pathname for output (default is printing to stdout)"
      )
      (
          "table,t",
          boost::program_options::value<fs::path>()->required()->default_value({}, "none"),
          "(optional) full pathname of translation-table"
      )
      (
          "input,i",
          boost::program_options::value<std::__1::vector<fs::path>>()->multitoken()->required(),
          "file(s) to handle"
      )
      ("html,H", po::bool_switch()->default_value(false), "set output-type to html")
      ("xml,X", po::bool_switch()->default_value(false), "set output-type to xml")
      (
          "filter,f",
          boost::program_options::value<std::__1::vector<std::string>>()->multitoken()->default_value({}, ""),
          "filter output for a style-name(s)"
      )
      ("sort,s", boost::program_options::value<std::string>()->default_value(""), "sort output for a field");

  store(parse_command_line(argc, argv, description), vm);
}

/**
 * Defines all argument constraints and checks them
 * @param vm the program arguments
 * @throws std::logic_error when any constraint is violated
 */
void checkConstraints(const po::variables_map &vm) {
  Requirements{vm}
      ("input");

  Conflicts{vm}
      ("html", "pdf");

  Dependencies{vm}
      ("html", "input")
      ("xml", "input")
      ("sort", "input")
      ("filter", "input");
}

/**
 * Main Program - Resolves command-line-arguments and prints output
 * @param argc number of command-line arguments
 * @param argv command-line arguments
 * @return program exit-code
 */
int main(int argc, char **argv) try {
  po::variables_map vm;
  po::options_description description("Allowed Options");
  parseCommandLine(argc, argv, vm, description);

  if (vm.count("help")) {
    std::cout << description << "\n";
    return 0;
  }

  checkConstraints(vm);

  const auto tablePath = vm["table"].defaulted() ? std::nullopt : std::optional(vm["table"].as<fs::path>());
  const Parser parser{tablePath, vm["filter"].as<std::vector<std::string>>(), vm["table"].defaulted()};
  const auto elements = parser.generate(
      vm["input"].as<std::vector<fs::path>>(),
      vm["sort"].as<std::string>().empty() ? std::nullopt : std::optional(vm["sort"].as<std::string>())
  );

  std::string output;
  if (vm["html"].as<bool>()) output = HtmlGenerator(elements).write();
  else if (vm["xml"].as<bool>()) output = XmlGenerator(elements).write();
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
  return 0;
} catch (std::exception &e) {
  std::cerr << e.what() << "\n";
  return -1;
}

