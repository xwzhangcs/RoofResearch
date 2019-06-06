from __future__ import print_function, division
import os
import torch
import torch.nn as nn
import pandas as pd
from skimage import io, transform
import numpy as np
import matplotlib.pyplot as plt
import torch.optim as optim
from torch.optim import lr_scheduler
import time
import copy
plt.switch_backend('agg')
from torch.utils.data import Dataset, DataLoader
from torchvision import transforms, utils, datasets, models
from lego_processing_data import MyDataset
from lego_processing_test_data import MyTestDataset
from PIL import Image
# Ignore warnings
import warnings
warnings.filterwarnings("ignore")

num_outputs = 6
num_epochs = 10
PATH = "test_60.pth"

if __name__ == "__main__":
    # Define transforms
    transformations = transforms.Compose([transforms.ToTensor(),
                                          transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
                                          ])
    # Define custom dataset
    test_data = MyTestDataset("test.csv", "data/test", transformations)
    # Define data loader
    test_dataset_loader = torch.utils.data.DataLoader(dataset=test_data, batch_size=1, shuffle=False)
    # GPU mode
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    # load model
    model = torch.load(PATH)

    # test model
    model.eval()
    for i_batch, test_batch in enumerate(test_dataset_loader):
        inputs = test_batch['input'].to(device)
        # labels = test_batch['output'].to(device)
        print(i_batch, inputs.size())
        outputs = model(inputs)
        print("outputs is {}".format(outputs))
        if i_batch > 5:
            break
        """
        if i_batch % 10 == 0 and i_batch < 100:
            inputs = test_batch['input'].to(device)
            # labels = test_batch['output'].to(device)
            print(i_batch, inputs.size())
            outputs = model(inputs)
            print("outputs is {}".format(outputs))
        elif i_batch % 10 != 0 and i_batch < 100:
            continue
        else:
            break

        """
        """
        loss = criterion(outputs.float(), labels.float())
        print("loss is {}".format(loss))
        print("------------Try again---------------")
        outputs = model(inputs)
        print("labels is {}, and outputs is {}".format(labels, outputs))
        loss = criterion(outputs.float(), labels.float())
        print("loss is {}".format(loss))
        if i_batch == 1:
            break
        """








