#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class State {
public:
    State(std::string name, double energyConsumption, long long stateSize)
        : name(name), energyConsumption(energyConsumption), stateSize(stateSize), percentageLandNeeded(0.0) {}

    void calculatePercentageLandNeeded(long long totalLandArea, double solarPanelEfficiency = 0.15, double wattsPerSqFt = 15.0) {
        double totalEnergyNeeded = energyConsumption * 1e12; // Convert to BTU
        double panelsNeeded = totalEnergyNeeded / (wattsPerSqFt * stateSize);
        double landAreaNeeded = panelsNeeded / solarPanelEfficiency;
        percentageLandNeeded = (landAreaNeeded / totalLandArea) * 100;
    }

    bool operator<(const State& other) const {
        return percentageLandNeeded < other.percentageLandNeeded;
    }

    friend std::ostream& operator<<(std::ostream& os, const State& state) {
        os << state.name << ": " << std::fixed << state.percentageLandNeeded << "% land needed";
        return os;
    }

private:
    std::string name;
    double energyConsumption; // Trillion BTU
    long long stateSize; // Square Feet
    double percentageLandNeeded;
};

int main() {
    std::vector<State> states;

    // Define the states and their data
    states.push_back(State("Texas", 13480.8, 7487580672000));
    states.push_back(State("California", 6922.8, 4563554688000));
    // Add data for the other states...

    long long totalUSLandArea = 3717792; // Total land area of the U.S. in square miles

    // Calculate the percentage of land needed for solar panels for each state
    for (State& state : states) {
        state.calculatePercentageLandNeeded(totalUSLandArea);
    }

    // Sort the states based on the percentage of land needed
    std::sort(states.begin(), states.end());

    // Display the ordered list
    for (const State& state : states) {
        std::cout << state << std::endl;
    }

    return 0;
}
