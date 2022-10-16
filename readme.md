# NeuralNetwork-C-Matrixs

## Description

### What is this?

A Simple DNN Implementation from scratch in c. Using Matrix and Vector to create weights and activations data structures.

### Environment

1. Mnist Task
    - require gcc to compile the mnist.c program
2. Visualization Task
    - require python3 + matplotlib to show the training accuracy progress image.
3. linus environment setup
    
    ```bash
    # install python3 and matplotlib
    sudo apt update
    sudo apt install software-properties-common
    sudo add-apt-repository ppa:deadsnakes/ppa
    sudo apt install python3.9
    sudo apt install python3-pip
    pip3 install matplotlib
    
    # install gcc
    sudo apt install build-essential
    sudo apt install make
    ```
    

## Model

### Adjust HyperParameter

1. open mnist.c
2. adjust define part 
    
    ```c
    #define INPUT_DIMENSIONS 784
    #define LAYER1_UNITS 128
    #define LAYER2_UNITS 10
    
    #define TRAIN_DATA_SIZE 60000
    #define CLASS_NUMS 10
    #define BATCH_SIZE 128
    #define LEARNING_RATE 0.001
    #define EPOCHS_NUMS 10001
    ```
    

### Train the model

1. open mnist.c 
    
    ```c
    // Make sure Train(); isn't annotationed.
    int main(void){
        Train();
        //Inference();
        return 0;
    }
    ```
2. compile mnist.c and run ./a.out

    ```bash
    make
    ```
    

### Visualization

1. show the accuracy progress by python
    
    ```c
    python3 visualization.py
    ```
    

### Inference the Model

1. After Training the model
2. Ensure layer1.params & layer2.params are in backups/ folders
3. open mnist.c
    
    ```c
    // Annotate Train();
    // Make sure Inference(); isn't annotationed.
    int main(void){
        //Train();
        Inference();
        return 0;
    }
    ```
4. compile mnist.c and run ./a.out

    ```bash
    make
    ```