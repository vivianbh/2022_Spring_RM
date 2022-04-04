close all;
clear;
clc;

%% read data
data = xlsread("HW4-1.xls");

% equation: yi = ai * x1 + bi * x2  for  i = 1, 2,..., 50
A = data(:, 1);
B = data(:, 2);
Y = data(:, 3);

%% derive the least squares method
m11 = A'*A; m12 = A'*B; m21 = B'*A; m22 = B'*B;
M = [m11 m12; m21 m22];
X = inv(M) * [A'*Y; B'*Y];

% solution
x1 = X(1)
x2 = X(2)