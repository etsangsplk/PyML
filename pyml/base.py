class BaseLearner:
    def __init__(self):
        pass

    def train(self, X, y=None):
        self._train(X, y)
        return self


class Predictor:
    
    def train_predict(self, X, y=None):
        self.train(X, y)
        return self.predict(X)

    def predict(self, X):
        return self._predict(X)

    def score(self, X, y_true):
        return self._score(X, y_true)


class Classifier:
    def __init__(self):
        pass

    def predict_proba(self, X):
        return self._predict_proba(X)


class Transformer:

    def __init__(self):
        pass

    def transform(self, X):
        return self._transform(X)

    def train_transform(self, X):
        self.train(X)
        self.transform(X)
