function time = getServiceTime(rand_value, data_table)
    % Function to retrieve service time based on a random value and data table
    % Inputs:
    %   rand_value - random value between 1 and 100
    %   data_table - cell array containing service times and probabilities
    % Output:
    %   time - corresponding service time based on the random value

    % Convert cell array to numeric array for probabilities
    probabilities = cellfun(@(x) x, data_table(2, :));
    cumulative_prob = cumsum(probabilities);


    % Scale the random value to be between 0 and 1
    scaled_rand_value = rand_value / 100;

    % Find the index corresponding to the scaled random value
    time_index = find(scaled_rand_value <= cumulative_prob, 1);
    
    % Error handling for invalid indices
    if isempty(time_index)
        error('No valid index found for random value in cumulative probabilities. Random value: %d, Cumulative probabilities: %s', rand_value, mat2str(cumulative_prob));
    end
    
    % Retrieve the corresponding service time
    time = data_table{1, time_index};
end
