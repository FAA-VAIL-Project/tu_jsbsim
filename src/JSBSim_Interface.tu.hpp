#ifndef TU_JSBSIM_INTERFACE_HPP
#define TU_JSBSIM_INTERFACE_HPP

/* external dependency includes */
#include <pybind11/pybind11.h>
#include "json/json.hpp"

/* JSBSim includes */
#include "FGFDMExec.h"
#include "models/FGMassBalance.h"
#include "models/FGPropulsion.h"
#include "models/propulsion/FGTank.h"

/* proprietary includes */
#include "AutoPilot.tu.hpp"
#include "pathing.h"
#include "Constants.tu.hpp"

namespace py = pybind11;

namespace tulsa
{

class JSBSim_Interface
{
    public:
    
    /* C++ Methods */
    void initializeJSBSim(void); // start the JSBSim engine, load configuration files.
    void writeManeuverConfiguration(std::string); // write a CUSTOM maneuver configuration key/value pairs using a JSON Payload.
    void writeManeuverConfiguration(void); // write DEFAULT the maneuver configuration key/value pairs using a JSON Payload.
    void setCommandedManeuver(int); // sets the commanded maneuver to autopilot.
    void runAutoPilot(int); // run the simulation for n iterations.
    void configureAircraftState(std::string); // write initial conditions for a new aircraft state.
    std::string readAircraftState(void); // get a JSON Payload of the aircraft state variables.
    std::string getExtendedJSBSimState(void); // get the status of every JSBSim flight executive parameter value
    void resetToInitialConditions(void); // run the initial conditions and one iteration of the autopilot control loop
    void configurePointMassStructure(std::string); // configure the individual point mass structure of the aircraft. Use configureAircraftState with a "weight-configuration" key.

    /* Python Methods*/
    void initializeJSBSimFromPython(void);
    void writeManeuverConfigurationFromPython(py::object);
    void setCommandedManeuverFromPython(py::object);
    void runAutoPilotFromPython(py::object);
    void configureAircraftStateFromPython(py::object);
    py::object readAircraftStateFromPython(void);
    py::object getExtendedJSBSimStateFromPython(void);
    void resetToInitialConditionsFromPython(void);
    void configurePointMassStructureFromPython(py::object);

    private:
    JSBSim::FGFDMExec FDM; // JSBSim flight executive.
    AutoPilot autopilot; // autopilot object, which makes control decisions based on its input.
    nlohmann::json aircraftstateJSONObject; // provides a COPY of the aircraft state. This object only updates when readAircraftState() is called.
};

} // namespace tulsa


#endif // TU_JSBSIM_INTERFACE_HPP
