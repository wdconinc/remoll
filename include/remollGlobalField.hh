#ifndef REMOLLGLOBALFIELD_HH
#define REMOLLGLOBALFIELD_HH

/*!
   \class remollGlobalField
   \brief Global field interface
*/

#include "G4MagneticField.hh"
#include "G4ThreeVector.hh"

#include <vector>

class G4GenericMessenger;
class G4EquationOfMotion;
class G4MagIntegratorStepper;
class G4ChordFinder;
class G4FieldManager;
class G4PropagatorInField;

class remollMagneticField;

class remollGlobalField : public G4MagneticField {
    public:
        remollGlobalField();
        ~remollGlobalField() override;

        void AddNewField(G4String& name);

        void SetInterpolationType(const G4String& name, const G4String& type);
        void SetZOffset(const G4String& name, G4double offset);
        void SetFieldScale(const G4String& name, G4double scale);
        void SetMagnetCurrent(const G4String& name, G4double current);

        void PrintFieldValue(const G4ThreeVector&);

        void GetFieldValue(const G4double[], G4double*) const override;

    private:
        /// Set the stepper
        void SetEquation();

        /// Set the stepper
        void SetStepper();

        /// Set the stepper
        void SetChordFinder();

    public:
        /// Set verbose level
        void SetVerboseLevel(G4int i) { fVerboseLevel = i; }

        /// Set the stepper types
        void SetEquationType(G4int i) { fEquationType = i; SetEquation(); }

        /// Set the stepper types
        void SetStepperType(G4int i) { fStepperType = i; SetStepper(); }

        /// Set the minimum step length
        void SetMinStep(G4double stp) { fMinStep = stp; SetAccuracyParameters(); }

        /// Set the delta chord length
        void SetDeltaChord(G4double dcr) { fDeltaChord = dcr; SetAccuracyParameters(); }

        /// Set the delta one step length
        void SetDeltaOneStep(G4double stp) { fDeltaOneStep = stp; SetAccuracyParameters(); }

        /// Set the delta intersection length
        void SetDeltaIntersection(G4double its) { fDeltaIntersection = its; SetAccuracyParameters(); }

        /// Set the minimum eps length
        void SetEpsMin(G4double eps) { fEpsMin = eps; SetAccuracyParameters(); }

        /// Set the maximum eps length
        void SetEpsMax(G4double eps) { fEpsMax = eps; SetAccuracyParameters(); }

        /// Set the accuracy parameters
        void SetAccuracyParameters();

        /// Print the accuracy parameters
        void PrintAccuracyParameters();

    private:
        G4int fEquationType{0};
        G4int fStepperType{4};

        G4double fMinStep;
        G4double fDeltaChord;
        G4double fDeltaOneStep;
        G4double fDeltaIntersection;
        G4double fEpsMin;
        G4double fEpsMax;

        G4EquationOfMotion*     fEquation{nullptr};
        G4int                   fEquationDoF{0};

        G4FieldManager*         fFieldManager{nullptr};
        G4PropagatorInField*    fFieldPropagator{nullptr};
        G4MagIntegratorStepper* fStepper{nullptr};
        G4ChordFinder*          fChordFinder{nullptr};

    private:
        static std::vector<remollMagneticField*> fFields;

        remollMagneticField* GetFieldByName(const G4String& name) const;

        G4GenericMessenger* fMessenger;
        G4GenericMessenger* fGlobalFieldMessenger;

        G4int fVerboseLevel{0};

};


#endif // REMOLLGLOBALFIELD_HH
