#include "ROOT/RDataFrame.hxx"
#include "TFile.h"
#include "TTree.h"

#include <string>
#include <stdexcept>
#include <cassert>

auto fileName("testtypeguessing.root");
auto treeName("myTree");

int main() {
   {
      TFile f(fileName, "RECREATE");
      TTree t(treeName, treeName);
      int b = 42;
      t.Branch("b", &b);
      std::string s = "fortytwo";
      t.Branch("s", &s);
      t.Fill();
      t.Write();
   }

   TFile f(fileName);
   ROOT::RDataFrame d(treeName, fileName);

   bool exception_caught = false;
   try {
      d.SupportsTreeBulkIO<double>("b");
   } catch (const std::runtime_error & re) {
      exception_caught = true;
      std::cerr << re.what();
   }
   R__ASSERT(exception_caught);

   return 0;
}
