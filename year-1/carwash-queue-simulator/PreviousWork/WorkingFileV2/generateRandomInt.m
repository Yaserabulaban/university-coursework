function randInt = generateRandomInt(lower, upper)
    % Generate a random integer between lower and upper bounds
    randInt = floor(lower + (upper - lower + 1) * rand());
end
