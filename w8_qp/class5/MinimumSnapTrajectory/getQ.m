function Q = getQ(n_seg, n_order, ts)
    Q = [];
    for k = 1:n_seg
        Q_k = [];
        T = ts(k);

        %############################################################
        %           Checkpoint1 : Finish the Q matrix
        % Reminder
        % parameters: Sigma7 Sigma6 Sigma5 Sigma4 Sigma3 Sigma2 Sigma1 Sigma0
        % You cannot directly copy the class slide!

        Q_k = [0];

        %############################################################
        
        
        Q_k = [840*840*(1/7)*T^7, 360*840*(1/6)*T^6, 120*840*(1/5)*T^5, 24*840*0.25*T^4, 0, 0, 0, 0;
               360*840*(1/6)*T^6, 360*360*0.2*T^5, 120*360*0.25*T^4, 24*360*(1/3)*T^3, 0, 0, 0, 0;
               120*840*0.2*T^5, 120*360*0.25*T^4, 120*120*(1/3)*T^3, 24*120*0.5*T^2, 0, 0, 0, 0;
               24*840*0.25*T^4, 24*360*(1/3)*T^3, 24*120*0.5*T^2, 24*24*T, 0, 0, 0, 0;
               0, 0, 0, 0, 0, 0, 0, 0;
               0, 0, 0, 0, 0, 0, 0, 0;
               0, 0, 0, 0, 0, 0, 0, 0;
               0, 0, 0, 0, 0, 0, 0, 0];   
        
        Q = blkdiag(Q, Q_k);
    end
end