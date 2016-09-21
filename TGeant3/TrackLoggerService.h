#include <TTree.h>
#include <TFile.h>
#include <TROOT.h>
#include <vector>
#include <iostream>

// singleton Logger class using a TTree
class Logger {

private:
  Logger() {
    ROOT::GetROOT();

    ffile = new TFile("/home/swenzel/AliceTracks.root","RECREATE");
    ftree = new TTree("ALICENextBdrTracks","");

    ftree->Branch("x",&x);
    ftree->Branch("y",&y);
    ftree->Branch("z",&z);
    ftree->Branch("dx",&dx);
    ftree->Branch("dy",&dy);
    ftree->Branch("dz",&dz);
    ftree->Branch("step",&step);
    ftree->Branch("depth",&depth);
    ftree->Branch("volId",&id);
    ftree->Branch("path",&path);   
    ftree->Branch("volname",&volname);
    ftree->Branch("class",&volclass);
  };
  const size_t kN = 1000000;
  
public:
  void AddEntry(float x_p, float y_p, float z_p, float dx_p, float dy_p, float dz_p, 
		float step_p, int depth_p, int id_p, std::string s_p, std::string voln_p, std::string class_p){
    x=x_p;y=y_p;z=z_p;dx=dx_p;dy=dy_p;dz=dz_p;id=id_p;path=s_p;
    step=step_p;
    depth=depth_p;
    volname = voln_p;
    volclass = class_p;
    ftree->Fill();
  }

  void FlushAndClose() {
    ffile->Write();
    ffile->Close();
  }
  
  static Logger& Instance() {
    static Logger instance;
    return instance;
  }


  // destructs and forces serialization to file via TTree
  /*
  ~Logger() {
    std::cerr << "****** SERIALIZING TRACK LOG ************\n";
    std::cerr << "****** " << fx.size() << "entries \n";
    std::cerr << "****** " << fy.size() << "entries \n";
    std::cerr << "****** " << fz.size() << "entries \n";
    std::cerr << "****** " << fdx.size() << "entries \n";
    std::cerr << "****** " << fdy.size() << "entries \n";
    std::cerr << "****** " << fdz.size() << "entries \n";
    std::cerr << "****** " << fVolIDs.size() << "entries \n";
    std::cerr << "****** " << fBranches.size() << "entries \n";
      for (size_t i=0;i<fx.size();++i){
        // set values;
        x=fx[i];
        y=fy[i];
        z=fz[i];
        dx=fdx[i];
        dy=fdy[i];
        dz=fdz[i];
        id=fVolIDs[i];
        path=fBranches[i];
	//        ftree->Fill();
      }
    ffile->Write();
    ffile->Close();
    // note that the tree object is deleted by the file at Close()
  }
  */

private:
  // data containers
  TFile *ffile;
  TTree *ftree;

  float x,y,z,dx,dy,dz;
  int id;
  int depth;
  float step;
  std::string path, volname, volclass;
};
