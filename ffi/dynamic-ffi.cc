#include <stdio.h>
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

#include "ffi-plugin.hh"
#include "dynamic-ffi.h"

using namespace clang::tooling;
using namespace clang;
using namespace llvm;
using namespace ffi;

static llvm::cl::OptionCategory MyToolCategory("my-tool options");

extern "C" int ctool_wrapper(int argc, const char **argv);

int ctool_wrapper(int argc, const char **argv) {
  CommonOptionsParser optparser(argc, argv, MyToolCategory); 
  ClangTool Tool(optparser.getCompilations(),
                 optparser.getSourcePathList());
  ffiPluginAction plugin;
  return Tool.run(newFrontendActionFactory<ffiPluginAction>().get());
}
