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
from PIL import Image
# Ignore warnings
import warnings
warnings.filterwarnings("ignore")

num_outputs = 8
num_epochs = 10
PATH = "roof_model_classifier.pth"

if __name__ == "__main__":
    # An instance of your model.
    # load model
    model = torch.load(PATH)
    # model = torch.load(PATH, map_location=lambda storage, loc: storage)
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    # device = torch.device("cpu")
    # An example input you would normally provide to your model's forward() method.
    example = torch.rand(1, 3, 224, 224).to(device)

    # Use torch.jit.trace to generate a torch.jit.ScriptModule via tracing.
    traced_script_module = torch.jit.trace(model, example)

    output = traced_script_module(torch.ones(1, 3, 224, 224).to(device))

    print(output[0, :8])

    traced_script_module.save("roof_model_classifier.pt")









