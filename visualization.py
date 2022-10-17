import matplotlib.pyplot as plt

def ShowLoss():
    pass 

def ShowAccuracy(path):
    with open(path) as f:
        accuracy = [line.rstrip() for line in f]
        for i in range(len(accuracy)):
            accuracy[i] = float(accuracy[i])
        plt.title("Training Process")
        plt.xlabel("Epochs")
        plt.ylabel("Accuracy")
        plt.ylim(-0.1, 1.1)
        plt.plot(accuracy)
        plt.show()

if __name__ == "__main__":
    ShowAccuracy("backups/accuracy.records")
