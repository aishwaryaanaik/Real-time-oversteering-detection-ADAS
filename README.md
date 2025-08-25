# Real-time-oversteering-detection-ADAS
This project talks about real time oversteering detection of vehicle using **Arduino Nano 33 BLE sense and ESP 32 with MPU 6050**.
## Introduction
Oversteering is when a vehicle **turns more than the driver intends**, often due to the rear wheels turning faster than the front wheels. This can cause the vehicle to lose control and spin out.
To detect oversteering in real-time, we monitored key vehicle dynamics: yaw rate, lateral acceleration, forward acceleration, and steering angle. These parameters, captured using **MPU6050 with ESP32 and Arduino Nano 33 BLE Sense**, were used to classify conditions as **normal (0) or oversteering (1)**. The system combines sensor data, a Decision Tree model, and embedded hardware for efficient and accurate detection.
<p align="center">
<img width="300" height="300" alt="image" src="https://github.com/user-attachments/assets/6daef83b-867d-4e1b-86a5-02680e3254e9" />
</p>

## Why this is important?
- According to the Ministry of Road Transport and Highways (MoRTH), in 2022, there were around 4.61 lakh road accidents in India, resulting in 1.68 lakh deaths and 4.43 lakh injuries.
- According to MoRTH's 2022 report, driver errors accounted for 77.3% of all accidents, and a significant number of these are related to loss of control while cornering or driving at high speeds.
- Speeding and Overtaking:In 2022, speeding was responsible for nearly 70% of fatal accidents in India.

## Prerequisites  

Before implementing the Oversteering Detection System, it’s important to understand the key **vehicle dynamics parameters** used for analysis.  

### Yaw Rate (ψ̇)  
-Yaw rate is the angular velocity of the vehicle around its vertical axis (Z-axis). It describes how quickly the car is rotating left or right.  
- **Equation**:  ψ̇ = dψ/dt
- where `ψ` = yaw angle (in radians).  
### Lateral accelration(a_y) 
- Acceleration acting perpendicular to the direction of travel (side force), experienced when a vehicle is cornering.  
- **Equation**:  a_y = v² / R
- where `v` = vehicle speed (m/s), `R` = turning radius (m).  
### Forward Acceleration (a_x)
- Acceleration along the direction of motion (longitudinal). It occurs during speeding up or slowing down.
- **Equation**:a_x = dv/dt
  
###  Steering Angle (δ)
-The angle between the direction of the front wheels and the longitudinal axis of the vehicle. It represents how much the driver has turned the steering wheel.
- **Approximate Relation with Yaw Rate** (Bicycle Model):
<br> ψ̇ ≈ (v / L) * δ
- where `v` = vehicle speed, `L` = wheelbase of vehicle, `δ` = steering angle.  
- **Unit**: Degrees (°) or Radians
  ### Decision Tree Model  

We used a **Decision Tree classifier** for oversteering detection.  

- **Concept**:  
  A decision tree splits data into branches based on rules (thresholds). Each internal node represents a condition on a feature, each branch represents an outcome, and each leaf node represents a final class label (Normal = 0, Oversteering = 1).  

- **Why Decision Tree?**  
  - Easy to interpret and visualize.  
  - Works well with small to medium datasets.  
  - Handles both numerical (sensor values) and categorical data.  
  - Low computational cost, making it suitable for **real-time embedded systems**. 


## Project flow
<p align="center">
<img width="700 height="500" alt="image" src="https://github.com/user-attachments/assets/bf6e59a1-1ab3-4445-bf28-870b65f63ca0" />
</p>

 1. **Data Collection**
    - The MPU 6050 integrated with ESP 32 is placed at the dashboard of the vehicle and from here lateral acceleration,forward acceleration and yaw rate is obtained.
Arduino Nano 33 BLE sense is used for obtaining steering angle.
- Data collection is done by using Arduino IDE and **CoolTerm2.4.0** and later converted into excel file.
<p align="center">
<img width="300" height="400" alt="image" src="https://github.com/user-attachments/assets/076c8bab-e478-43c0-8463-34d2a5798233" />
</p>

2.**Data Labeling**
-The data set is labeled based on parameters considered such as **yaw rate,lateral acceleration,forward acceleration,steering angle**.
-For each data sample,thresholds were set for each parameter based on experimental analysis (vehicle dynamics limits).
 - If |ψ̇| > threshold_yaw **and** |a_y| > threshold_lat→ Likely **Oversteering**.  
   - If values remain within safe ranges → **Normal condition**.
### Normal Range Thresholds  

We set safe ranges for sensor values. If readings go outside these limits, the system labels it as **Oversteering (1)**, otherwise as **Normal (0)**.  

-Forward Acceleration (X-axis) in m/s^2
-5.0   <= Accel_X <=  5.0    

-Lateral Acceleration (Y-axis) in m/s^2
-3.0   <= Accel_Y <=  3.0    

-Yaw Rate (Gyro Z-axis) in rad/s
-0.5   <= Gyro_Z  <=  0.5    

-Steering Angle (Gyro Y-axis) in °/s
-100.0 <= Gyro_Y  <= 100.0  
3. **Model Training (Software)**  
   - Algorithm: **Decision Tree** (Scikit-learn, Python).  
   - Dataset split: `80% training / 20% testing`.
4. **Hardware Implementation**  
   - **ESP32 + MPU6050**: Reads acceleration & gyroscope values, sends processed data.  
   - **Arduino Nano 33 BLE Sense**: Captures steering angle.  
   - **Output**: LED indication when oversteering is detected in real-time.
     
5. **Testing & Validation**  
   - Tested with unseen driving conditions.  
   - Verified accuracy of model + hardware LED alerts.
## Results
- **Software**:Decision tree model achieved nearly 99% accuracy
- **Hardware**: LED on ESP32 blinks when oversteering is detected.
  <p align="center">
  <img width="300" height="450" alt="image" src="https://github.com/user-attachments/assets/f57eaf3a-db52-4973-8202-fd843b5282a7" />
</p>

  ## Co-Authors
  - Devika Vijapur, Nidhi Desai, Smita Ganur.












