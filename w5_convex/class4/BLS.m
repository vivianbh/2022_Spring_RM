function [t] = BLS(x1,x2,t,gradient1,gradient2,fg)
    % x1, x2 is variable
    % gradient1 is x1's gradient, and gradient2 is x2's graditent
    % t is step size , the one you need to iterate
    % fg is the function handle, you can directly use fg(x) to call the
    % function
    

% Apply your code here
    alpha = 0.3;
    beta = 0.8;
    
    rans = fg( x1+t*(-0.1*gradient1), x2+t*(-1*gradient2) );
    aans = fg(x1, x2) - alpha * t * (0.1*gradient1^2 +1*gradient2^2); 
    while rans > aans
         t = t * beta;
    end

end