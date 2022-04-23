function [R_d] = LinearOptimization(P_lo, Np, P_origin)

    
    % We have the relation P_after = R_d * P_origin, but we should
    % convert the equation into "P_after = P_origin * R_d" form, because we 
    % want to solve R_d, not P_origin


    % turn P_after into  3N x 1
    P_after = reshape(P_lo,Np*3,1);
    
    
    % P_origin_cat will be arrange into 3N x 9
    P_origin_cat = [];
    
    for i=1:1:Np
        P_origin_cat = cat(1,P_origin_cat,matrix_change(P_origin(:,i)'));
    end
     
    % R_d is a 9x1 matrix
    R_d = (P_origin_cat'*P_origin_cat) \ (P_origin_cat'*P_after);

    % reshape R_d into 3x3 matrix
    R_d = reshape(R_d,3,3);
    
end
