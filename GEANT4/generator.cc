#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	fParticleGun = new G4ParticleGun(1); //1 primary vertex per event 
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName = "e+";
	G4ParticleDefinition *particle = particleTable->FindParticle("e+");

	G4ThreeVector pos(0., 0., 0.);
	G4ThreeVector mom(0., 0., 1.);

	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	fParticleGun->SetParticleMomentum(0.001 * GeV);
	fParticleGun->SetParticleDefinition(particle);

	fParticleGun->GeneratePrimaryVertex(anEvent);
}