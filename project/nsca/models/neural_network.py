import tensorflow as tf
from tensorflow.keras.models import Model
from tensorflow.keras.layers import Input, Dense, Dropout, Flatten, Conv2D, MaxPooling2D
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.callbacks import EarlyStopping, ModelCheckpoint
from sklearn.preprocessing import StandardScaler
import numpy as np

class NeuralNetwork:
    def __init__(self, input_shape, num_classes, pre_trained_model=None):
        self.input_shape = input_shape
        self.num_classes = num_classes
        self.pre_trained_model = pre_trained_model
        self.model = self.build_model()

    def build_model(self):
        inputs = Input(shape=self.input_shape)
        x = Conv2D(32, (3, 3), activation='relu', input_shape=self.input_shape)(inputs)
        x = MaxPooling2D((2, 2))(x)
        x = Conv2D(64, (3, 3), activation='relu')(x)
        x = MaxPooling2D((2, 2))(x)
        x = Conv2D(128, (3, 3), activation='relu')(x)
        x = MaxPooling2D((2, 2))(x)
        x = Flatten()(x)
        x = Dense(128, activation='relu')(x)
        x = Dropout(0.2)(x)
        outputs = Dense(self.num_classes, activation='softmax')(x)
        model = Model(inputs=inputs, outputs=outputs)
        model.compile(optimizer=Adam(lr=0.001), loss='categorical_crossentropy', metrics=['accuracy'])
        return model

    def train(self, X_train, y_train, X_val, y_val, epochs=10, batch_size=32):
        early_stopping = EarlyStopping(monitor='val_loss', patience=5, min_delta=0.001)
        model_checkpoint = ModelCheckpoint('best_model.h5', monitor='val_loss', save_best_only=True, mode='min')
        self.model.fit(X_train, y_train, epochs=epochs, batch_size=batch_size, validation_data=(X_val, y_val), callbacks=[early_stopping, model_checkpoint])

    def evaluate(self, X_test, y_test):
        loss, accuracy = self.model.evaluate(X_test, y_test)
        return accuracy

    def predict(self, X):
        return self.model.predict(X)

    def load_pre_trained_model(self):
        if self.pre_trained_model:
            self.model.load_weights(self.pre_trained_model)
