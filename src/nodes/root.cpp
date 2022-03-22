#include "root.h"

#include "core/context.h"

llvm::Value *Root::Codegen() {
  for (auto &child : this->children) {
    child->Codegen();
  }

  auto targetTriple = llvm::sys::getDefaultTargetTriple();

  llvm::InitializeAllTargetInfos();
  llvm::InitializeAllTargets();
  llvm::InitializeAllTargetMCs();
  llvm::InitializeAllAsmParsers();
  llvm::InitializeAllAsmPrinters();

  std::string error;
  auto target = llvm::TargetRegistry::lookupTarget(targetTriple, error);

  if (!target) {
    ERROR(error);
  }

  llvm::TargetOptions opts;
  auto targetMachine = target->createTargetMachine(
      targetTriple, "generic", "", opts, llvm::Optional<llvm::Reloc::Model>());

  Context::Get()->module->setDataLayout(targetMachine->createDataLayout());
  Context::Get()->module->setTargetTriple(targetTriple);

  auto filename = "output.o";
  std::error_code errorCode;
  llvm::raw_fd_ostream dest(filename, errorCode, llvm::sys::fs::OF_None);

  if (errorCode) {
    ERROR("Could not open output.o for reason: {}", errorCode.message());
  }

  llvm::legacy::PassManager pass;
  auto FileType = llvm::CGFT_ObjectFile;

  if (targetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
    ERROR("Target machine cannot emit an object file")
  }

  pass.run(*Context::Get()->module);
  dest.flush();

  Context::Get()->module->print(llvm::errs(), nullptr);
  Context::Get()->module = std::make_unique<llvm::Module>("progam", Context::Get()->context);

  std::system("gcc output.o -no-pie -o program && gnome-terminal -- bash -c './program && read'");

  return nullptr;
}