function [R_d] = LinearOptimization(P_after, Np, P_origin)

    
    % We have the relation P_after = R_d * P_origin, but we should
    % convert the equation into "P_after = P_origin * R_d" form, because we 
    % want to solve R_d, not P_origin

    % implement your code here

    % matrix_change[]
       
    R_Np = inv(P_after' * P_after) * P_after' * P_origin;
    R_d = P_after * R_Np / P_after;
    
end
