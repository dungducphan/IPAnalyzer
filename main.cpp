#include <tinytiffreader.hxx>
#include <TString.h>
#include <iostream>
#include <TGraph2D.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TH2.h>

int main() {

  TGraph2D* gr = new TGraph2D();

  TinyTIFFReaderFile* tiffr = nullptr;
  tiffr = TinyTIFFReader_open("/home/dphan/learning/muonTomo/rawData/2022-02-23-selected/14557 SR 10-PMT-600-[Phosphor].tif");
	if (!tiffr) { 
     std::cout << " ERROR reading (not existent, not accessible or no TIFF file)." << std::endl; 
  } else { 
     if (TinyTIFFReader_wasError(tiffr)) {
       std::cout << " ERROR: " << TinyTIFFReader_getLastError(tiffr) << std::endl; 
     } else {
         std::cout << " ImageDescription: " << std::endl << TinyTIFFReader_getImageDescription(tiffr) << std::endl; 
         uint32_t frames = TinyTIFFReader_countFrames(tiffr); 
         std::cout << " frames: " << frames << std::endl; 
         uint32_t frame = 0; 
         if (TinyTIFFReader_wasError(tiffr)) {
           std::cout << " ERROR:" << TinyTIFFReader_getLastError(tiffr) << std::endl; 
         } else {
             do { 
                 const uint32_t width=TinyTIFFReader_getWidth(tiffr); 
                 const uint32_t height=TinyTIFFReader_getHeight(tiffr); 
                 const uint16_t samples=TinyTIFFReader_getSamplesPerPixel(tiffr);
                 const uint16_t bitspersample=TinyTIFFReader_getBitsPerSample(tiffr, 0);
                 bool ok = true;
                 std::cout << " size of frame " << frame << ": " << width << "x" << height << std::endl; 
                 std::cout << " each pixel has " << samples << " samples with " << bitspersample << " bits each" << std::endl; 
                 if (ok) { 
                     frame++; 
                     // allocate memory for 1 sample from the image
                     uint16_t* image = (uint16_t*) calloc(width*height, bitspersample/8);  
                     
                     for (uint16_t sample=0; sample<samples; sample++) {
                         // read the sample
                         TinyTIFFReader_getSampleData(tiffr, image, sample); 
                         if (TinyTIFFReader_wasError(tiffr)) { 
														ok = false; 
														std::cout << " ERROR:" << TinyTIFFReader_getLastError(tiffr) << std::endl; 
														break; 
												 } 
												 
                         for (unsigned int i = 0; i < height; ++i) {
                           for (unsigned int j = 0; j < width; ++j) {
                            std::cout << Form("%05i %05i %06i", j, i, (short unsigned int) image[j + width * i]) << std::endl;
                            // gr->AddPoint(j, i, (short int) image[j + width * i]);
                           }
                         }
                
                         // HERE WE CAN DO SOMETHING WITH THE SAMPLE FROM THE IMAGE 
                         // IN image (ROW-MAJOR!)
                         // Note: That you may have to typecast the array image to the
                         // datatype used in the TIFF-file. You can get the size of each
                         // sample in bits by calling TinyTIFFReader_getBitsPerSample() and
                         // the datatype by calling TinyTIFFReader_getSampleFormat().
                         
                     }
                     
                     free(image); 
                 } 
             } while (TinyTIFFReader_readNext(tiffr)); // iterate over all frames
             std::cout << " read " << frame << " frames" << std::endl; 
         }
     }
 	}   
 	TinyTIFFReader_close(tiffr); 

  // gStyle->SetOptStat(0);
  // TCanvas* c = new TCanvas("c", "c", 80000, 40000);
  // gr->Draw("SURF1");
  // TH2D* h = (TH2D*) gr->GetHistogram();
  // h->Draw("COLZ");
  // c->SaveAs("MuonImage.pdf");

  return 0;
}


