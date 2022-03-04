#include <fstream>
#include <iostream>
#include <TH2.h>

void test() {
  std::ifstream raw("./raw.txt");
  int x, y, val;
  TH2S* h = new TH2S("h", "", 8000, 0, 8000, 4000, 0, 4000);
  while (raw >> x >> y >> val) {
    // std::cout << Form("%05i, %05i, %06i", x, y, val) << std::endl;
    int bx = h->GetXaxis()->FindBin(x + .5);
    int by = h->GetYaxis()->FindBin(y + .5);
    h->SetBinContent(bx, by, val);
  }
  gStyle->SetOptStat(0);
  h->Draw("COLZ");
}
