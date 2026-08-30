function time = getTimeFromRange(rand_value, data_table)
    % Ensure data_table is a cell array
    if ~iscell(data_table)
        error('data_table must be a cell array');
    end

    % Convert cell array to numeric array
    probabilities = cellfun(@(x) x, data_table(2, :));
    cumulative_prob = cumsum(probabilities);

    % Debug: Check data_table, probabilities, and cumulative_prob content
    disp('Debug: Checking data_table content');
    disp(data_table);
    disp('Debug: Checking probabilities content');
    disp(probabilities);
    disp('Debug: Checking cumulative_prob content');
    disp(cumulative_prob);

    scaled_rand_value = rand_value / 100; % Scale the random value to be between 0 and 1
    time_index = find(scaled_rand_value <= cumulative_prob, 1);
    if isempty(time_index)
        error('No valid index found for random value in cumulative probabilities.');
    end
    time = data_table{1, time_index};
end
