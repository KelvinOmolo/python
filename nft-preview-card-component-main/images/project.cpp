// Constants
const float V_fixed = 12.0;            // Fixed voltage supplied to Arduino for reference
const float ACS712_SENSITIVITY = 0.185; // ACS712 sensitivity in V/A for ACS712ELCTR-05B
const float Rho_A_ratio = 50.0;        // Resistivity-to-area ratio in ohms/m^2

// Variables
float R_per_unit_length;               // Resistance per unit length
float I_normal;                        // Normal current
float I_fault;                         // Fault current
float ∆R;                              // Change in resistance
float faultLocation;                   // Estimated fault location

void setup() {
  // Initialize sensors, communication modules, etc.
  R_per_unit_length = Rho_A_ratio;     // Set resistance per unit length
  Serial.begin(9600);                   // Initialize serial communication
}

void loop() {
  // Simulate obtaining current from the ACS712 sensor
  float currentFromSensor = getCurrentFromACS712();

  // Calculate Normal Current
  I_normal = calculateNormalCurrent(V_fixed);

  // Calculate Fault Current (simulated using the sensor value)
  I_fault = currentFromSensor;

  // Check for Fault
  if (isFaultDetected(I_normal, I_fault)) {
    // Calculate Change in Resistance
    ∆R = calculateResistanceChange(V_fixed, I_fault);

    

    // Display Fault Information
    displayFaultInformation(I_fault, faultLocation);
  } else {
    // Display Normal Current
    Serial.println("Normal Current: " + String(I_normal) + " A");
  }

  // Repeat
  delay(1000);  // Adjust based on desired sampling rate
}

// Simulate obtaining current from the ACS712 sensor
float getCurrentFromACS712() {
  // In a real scenario, read the current from the ACS712 sensor
  // For simulation purposes, generate a random value between 0A and 5A
  return random(0, 5);
}

// Function to calculate normal current using Ohm's Law
float calculateNormalCurrent(float voltage) {
  return voltage / (R_per_unit_length * ACS712_SENSITIVITY);
}

// Function to check if a fault is detected
bool isFaultDetected(float normalCurrent, float faultCurrent) {
  // Compare normal current with fault current to detect a fault
  return faultCurrent > (1.2 * normalCurrent);  // Example threshold for fault detection
}

// Function to calculate change in resistance using Ohm's Law
float calculateResistanceChange(float voltage, float current) {
  return voltage / (current * ACS712_SENSITIVITY);
}

// Function to estimate fault location using Ohm's Law
float estimateFaultLocation(float resistanceChange) {
  return resistanceChange / R_per_unit_length;
}

// Function to display fault information
void displayFaultInformation(float faultCurrent, float faultLocation) {
  Serial.println("Fault Detected!");
  Serial.println("Fault Current: " + String(faultCurrent) + " A");
  Serial.println("Estimated Fault Location: " + String(faultLocation) + " meters");
}
