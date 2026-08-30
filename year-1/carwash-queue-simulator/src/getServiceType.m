function serviceType = getServiceType(rand_value, data_table)
    % Function to retrieve service type based on a random value and data table
    % Inputs:
    %   rand_value - random value between 1 and 100
    %   data_table - cell array containing service types and probabilities
    % Output:
    %   serviceType - corresponding service type based on the random value

    % Convert cell array to numeric array for probabilities
    probabilities = cellfun(@(x) x, data_table(2, :));
    cumulative_prob = cumsum(probabilities);


    % Scale the random value to be between 0 and 1
    scaled_rand_value = rand_value / 100;

    % Find the index corresponding to the scaled random value
    type_index = find(scaled_rand_value <= cumulative_prob, 1);
    
    % Retrieve the corresponding service type
    serviceType = data_table{1, type_index};
end
