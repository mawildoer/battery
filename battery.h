#ifndef BATTERY_H
#define BATTERY_H

const unsigned int battery_profile_voltage_divisions = 21; // 5% increments

class battery {
public:
  // Charge profiles
  // Arrary lengths must be specified: https://stackoverflow.com/questions/21152171/too-many-initializers-for-int-0-c
  struct profile_t {
    float voltage[battery_profile_voltage_divisions];
    int lowCharge;
    int highCharge;
  };

  // Table from: https://www.rcgroups.com/forums/showthread.php?2245385-Lipoly-Voltage-vs-State-Of-Charge-(Remaining-Capacity
  static constexpr profile_t generic_lipo = {
    {3.27,3.61,3.69,3.71,3.73,3.75,3.77,3.79,3.8,3.82,3.84,3.85,3.87,3.91,3.95,3.98,4.02,4.08,4.11,4.15,4.2}, // Voltage
    15, // Low charge
    95 // High charge
  };

private:
  unsigned int cells;
  profile_t profile;

  int chargeAtIndex (int i) {
    return i*5;
  }

public:
  battery (profile_t profile, int cells): cells(cells), profile(profile) {}
  battery (profile_t profile): cells(1), profile(profile) {}

  int lowCharge () {
    return profile.lowCharge;
  }

  int highCharge () {
    return profile.highCharge;
  }

  int charge (float battery_voltage) {
    int i = 0;

    if (profile.voltage[0] > battery_voltage) return 0; // voltage below charts

    while (i < battery_profile_voltage_divisions) {
      if (profile.voltage[i] < battery_voltage) i++;
      else {
        // Scanner found the correct
        float m = (chargeAtIndex(i) - chargeAtIndex(i-1))/(profile.voltage[i] - profile.voltage[i-1]);
        float c = chargeAtIndex(i) - (m * profile.voltage[i]);

        return (int)(battery_voltage * m + c);
      }
    }

    return 100; // Voltage over chart
  }
};

constexpr battery::profile_t battery::generic_lipo; // declaration of lipo profile

#endif
