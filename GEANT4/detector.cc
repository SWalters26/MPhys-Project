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

	//G4cout << "Photon position: " << posPhoton << G4endl; //likly not known

	const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();

	G4int copyNo = touchable->GetCopyNumber(); 

	//G4cout << "Copy number: " << copyNo << G4endl;//will give us the position in the i and j variables defined before (i.e. detector number)

	G4VPhysicalVolume* physVol = touchable->GetVolume();
	G4ThreeVector posDetector = physVol->GetTranslation();

	G4cout << "Detector position: " << posDetector << G4endl; //will give us the detector position when detector is hit by a photon

	return true;
}