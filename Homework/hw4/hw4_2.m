close all;
clear;
clc;
syms q1 q2 q3 q4 ax ay az

% read data: measurement of the accelerometer
acc = xlsread("HW4-2.xls");

g = -9.8;
error = @(q1, q2, q3, q4, ax, ay, az) [-2*g*(q2*q4-q1*q3)-ax;
                                       -2*g*(q1*q2+q3*q4)-ay;
                                       -2*g*(0.5-q2^2-q3^2)-az];
J = @(q1, q2, q3, q4) -2*g*[-q3 q4 -q1 q2;
                             q2 q1  q4 q3;
                             0 -2*q2 -2*q3 0];

iter = 400;
[R, C] = size(acc);
quaternion = zeros(R, 4);

%% gradient descent
for k = 1:R
    
    % initial value
    q = [1; 0; 0; 0];
    t = 0.8;
    
    count = 0;
    
    while count < iter
        
        e = error(q(1), q(2), q(3), q(4), acc(k, 1), acc(k, 2), acc(k, 3));
        J_q = J(q(1), q(2), q(3), q(4));
        step_size = BLS(q, t, acc(k, :), error, J);

        q = q - step_size * (J_q' * e) / norm(J_q' * e);
        
        gradient_c = J(q(1), q(2), q(3), q(4))' * error(q(1), q(2), q(3), q(4), acc(k, 1), acc(k, 2), acc(k, 3));
        
        if norm(gradient_c) < 0.9 
            break;
        end
        
        count = count + 1;
    end
    
    quaternion(k, :) = q';
end

%% verify error
result_error = ones(R, 3);

for k = 1:R
    
    result_error(k, :)= abs(error(quaternion(k,1), quaternion(k, 2), quaternion(k, 3), quaternion(k,4), acc(k, 1), acc(k, 2), acc(k,3))');

end

%% optput the result q
name = ["q1", "q2", "q3", "q4"];
data = cat(1, name, quaternion);
writematrix(data, "HW4-2_solution.xls");