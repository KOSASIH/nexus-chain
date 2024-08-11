import numpy as np
import pandas as pd
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split

class DataLoader:
    def __init__(self, data_path, batch_size=32):
        self.data_path = data_path
        self.batch_size = batch_size
        self.data = self.load_data()

    def load_data(self):
        data = pd.read_csv(self.data_path)
        X = data.drop(['label'], axis=1)
        y = data['label']
        X_train, X_val, y_train, y_val = train_test_split(X, y, test_size=0.2, random_state=42)
        scaler = StandardScaler()
        X_train = scaler.fit_transform(X_train)
        X_val = scaler.transform(X_val)
        return X_train, y_train, X_val, y_val

    def get_batch(self):
        X_train, y_train, X_val, y_val = self.data
        indices = np.random.choice(X_train.shape[0], self.batch_size, replace=False)
        X_batch = X_train[indices]
        y_batch = y_train[indices]
        return X_batch, y_batch
