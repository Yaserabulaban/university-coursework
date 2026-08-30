function printInterArrivalTimeTable(interArrival_Data)
    % Function to print the inter-arrival time table
    % Inputs:
    %   interArrival_Data - cell array containing inter-arrival time data
    % Output:
    %   None

    % Validate input
    if ~iscell(interArrival_Data) || size(interArrival_Data, 1) ~= 4
        error('Input must be a cell array with 4 rows: [Inter-arrival Time, Probability, CDF, Range]');
    end

    % Print table header
    fprintf('%-20s%-15s%-15s%-15s\n', 'Inter-arrival Time', 'Probability', 'CDF', 'Range');
    
    % Print each row of the inter-arrival time table
    for i = 1:size(interArrival_Data, 2)
        fprintf('%-20d%-15.2f%-15.2f%-15s\n', interArrival_Data{1, i}, interArrival_Data{2, i}, interArrival_Data{3, i}, interArrival_Data{4, i});
    end
    fprintf('\n');
end
