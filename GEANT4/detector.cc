#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *R0hist)
{
	G4Track *track = aStep->GetTrack();

	track->SetTrackStatus(fStopAndKill); //kills the photon once its been detected to avoid double counting 

	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
	G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

	G4ThreeVector posPhoton = preStepPoint->GetPosition();
	G4ThreeVector momPhoton = preStepPoint->GetMomentum();

	G4double wlen = (1.239841939 * eV / momPhoton.mag()) * 1E+03;

	//G4cout << "Photon position: " << posPhoton << G4endl; //likly not known

	const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();

	G4int copyNo = touchable->GetCopyNumber(); 

	//G4cout << "Copy number: " << copyNo << G4endl;//will give us the position in the i and j variables defined before (i.e. detector number)

	G4VPhysicalVolume *physVol = touchable->GetVolume();
	G4ThreeVector posDetector = physVol->GetTranslation();

	G4cout << "Detector position: " << posDetector << G4endl; //will give us the detector position when detector is hit by a photon

	G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

	G4AnalysisManager *man = G4AnalysisManager::Instance();

	man->FillNtupleIColumn(0, 0, evt);
	man->FillNtupleDColumn(0, 1, posPhoton[0]);
	man->FillNtupleDColumn(0, 2, posPhoton[1]);
	man->FillNtupleDColumn(0, 3, posPhoton[2]);
	man->FillNtupleDColumn(0, 4, wlen);
	//man->AddNtupleRow(0);

	man->FillNtupleIColumn(1, 0, evt);
	man->FillNtupleDColumn(1, 1, posDetector[0]);
	man->FillNtupleDColumn(1, 2, posDetector[1]);
	man->FillNtupleDColumn(1, 3, posDetector[2]);
	man->AddNtupleRow(1);

	return true;
}