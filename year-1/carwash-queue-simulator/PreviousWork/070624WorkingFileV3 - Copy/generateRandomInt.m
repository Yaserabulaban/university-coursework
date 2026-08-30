function randInt = generateRandomInt(lower, upper)
    % Generate a random integer between lower and upper bounds
    randInt = floor(lower + (upper - lower + 1) * rand());

    % Debug: Check randInt content
    disp('Debug: Checking randInt content');
    disp(randInt);
end
