function time = getTimeFromRange(rand_value, data_table)
    % Function to retrieve time based on a random value and data table
    % Inputs:
    %   rand_value - random value between 1 and 100
    %   data_table - cell array containing times and probabilities
    % Output:
    %   time - corresponding time based on the random value

    % Ensure data_table is a cell array
    if ~iscell(data_table)
        error('data_table must be a cell array');
    end

    % Convert cell array to numeric array for probabilities
    probabilities = cellfun(@(x) x, data_table(2, :));
    cumulative_prob = cumsum(probabilities);

    % Scale the random value to be between 0 and 1
    scaled_rand_value = rand_value / 100;

    % Find the index corresponding to the scaled random value
    time_index = find(scaled_rand_value <= cumulative_prob, 1);

    if isempty(time_index)
        error('No valid index found for random value in cumulative probabilities.');
    end

    % Retrieve the corresponding time
    time = data_table{1, time_index};
end
