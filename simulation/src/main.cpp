#include "../include/Application.h"
#include "../include/config.h"
#include "../include/integrators/verlet.h"
#include "../include/scenarios/billiards.h"
#include "../include/scenarios/solar_system.h"

int main()
{
    const Config cfg = load_config("config.json");

    billiards_scenario    billiards;
    solar_system_scenario solar;

    ScenarioManager scenes;
    scenes.add(billiards);
    scenes.add(solar);

    Application app(std::move(scenes), std::make_unique<verlet_integrator>(), cfg);
    app.run();
}
