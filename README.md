# Battery

Battery monitoring library written for Arduino, but generic enough that it may easily be implemented in any c++ environment

## Usage

Basic voltage to charge level for a generic lipo:

```cpp
battery lipo(battery::generic_lipo);
float battery_voltage = xxx; // In volts
int charge_percentage = lipo.charge(battery_voltage);
```

Battery profiles also contain low and high charge information to improve battery monitoring an allow for safe power off.

```cpp
lipo.lowCharge() // returns low charge charge percentage
lipo.highCharge() // returns high charge charge percentage
```

Battery profiles can also be easily created.
 - battery_profile_voltage_divisions (default 21 or 5% increment) battery voltages array
 - low charge level (where ideally you don't draw below without impacting battery life)
 - high charge level (where ideally you don't charge above without impacting battery life)


```cpp
battery::profile_t exampleProfile = {
  {3.27,3.61,3.69,3.71,3.73,3.75,3.77,3.79,3.8,3.82,3.84,3.85,3.87,3.91,3.95,3.98,4.02,4.08,4.11,4.15,4.2}, // Voltage
  15, // Low charge
  95 // High charge
};
```

Mutli-cell packs can also be instasiated without updating the profile itself:
```cpp
battery lipo(battery::generic_lipo, 2); // for a 2 cell pack
```
