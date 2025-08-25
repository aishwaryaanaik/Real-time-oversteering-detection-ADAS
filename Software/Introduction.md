## Software Implementation  

The software part of the project was developed in **Python** using the **Scikit-learn** library.  
- Collected sensor data was stored in `dataset.csv`.  
- A **Decision Tree classifier** was trained on this dataset (80% training, 20% testing).  
- The model achieved **nearly 99% accuracy** in distinguishing between **Normal (0)** and **Oversteering (1)** conditions.  
- A separate script allows **real-time testing** where new sensor values or user inputs can be classified instantly.  
