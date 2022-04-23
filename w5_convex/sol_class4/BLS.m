function [t] = BLS(x1,x2,t,gradient1,gradient2,fg)

    alpha = 0.5;
    beta = 0.7;
    while fg((x1 + t*(-gradient1)),(x2 + t*(-gradient2))) >= fg(x1,x2) - alpha*t*(gradient1^2 + gradient2^2)
    
        t = t*beta;
    
    end

end