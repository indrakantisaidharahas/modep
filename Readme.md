# Random Forest Inference Engine (C++)

A C++ implementation of a Random Forest inference system that performs predictions using a pre-trained model stored in binary format.

## Overview

This project focuses on the **inference stage of a Random Forest model**. It loads a serialized forest structure and performs predictions by traversing decision trees from root to leaf for each input sample.

## Methodology

- We all know the  Random Forest is ntg but  a collection of decision trees.
- Each tree is stored using array-based structures:
  - `left` and `right` child indices
  - `feature` index used for splitting
  - `threshold` values for decision boundaries
  - `value` stored at leaf nodes
- Input samples are passed through each tree individually.
- Each tree produces a prediction based on leaf node output.
- Final output is obtained using majority voting across all trees.

