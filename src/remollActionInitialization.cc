/*
 * remollUserActionInitialization.cc
 *
 *  Created on: May 1, 2017
 *      Author: wdconinc
 */

#include "remollActionInitialization.hh"

#include "remollRunAction.hh"
#include "remollEventAction.hh"
#include "remollTrackingAction.hh"
#include "remollSteppingAction.hh"
#include "remollPrimaryGeneratorAction.hh"

void remollActionInitialization::Build() const
{
  // Run action
  auto* run_action = new remollRunAction();
  SetUserAction(run_action);

  // Event action
  auto* event_action = new remollEventAction();
  SetUserAction(event_action);

  // Tracking action
  auto* tracking_action = new remollTrackingAction();
  SetUserAction(tracking_action);

  // Stepping action
  auto* stepping_action = new remollSteppingAction();
  SetUserAction(stepping_action);

  // Primary generator action
  auto* gen_action = new remollPrimaryGeneratorAction();
  SetUserAction(gen_action);
  event_action->SetPrimaryGeneratorAction(gen_action);
}

void remollActionInitialization::BuildForMaster() const
{
  // Run action
  auto* run_action = new remollRunAction();
  SetUserAction(run_action);
}
