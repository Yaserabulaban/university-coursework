function randInt = generateRandomInt(lower, upper)
    % Function to generate a random integer between lower and upper bounds
    % Inputs:
    %   lower - lower bound of the range
    %   upper - upper bound of the range
    % Output:
    %   randInt - generated random integer

    % Validate inputs
    if ~isnumeric(lower) || ~isscalar(lower) || floor(lower) ~= lower
        error('Lower bound must be an integer.');
    end
    if ~isnumeric(upper) || ~isscalar(upper) || floor(upper) ~= upper
        error('Upper bound must be an integer.');
    end
    if lower > upper
        error('Lower bound must be less than or equal to upper bound.');
    end

    % Generate a random integer between lower and upper bounds
    randInt = floor(lower + (upper - lower + 1) * rand());

end
