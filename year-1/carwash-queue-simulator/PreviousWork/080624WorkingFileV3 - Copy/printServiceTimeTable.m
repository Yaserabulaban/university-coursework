function printServiceTimeTable(washBayName, data)
    % Function to print the service time table for a given wash bay
    % Inputs:
    %   washBayName - name of the wash bay
    %   data - cell array containing service time data
    % Output:
    %   None

    fprintf('%s:\n', washBayName);
    fprintf('%-15s%-15s%-15s%-15s\n', 'Service Time', 'Probability', 'CDF', 'Range');
    
    % Debug: Check data content (comment out in production)
    % disp('Debug: Checking data content');
    % disp(data);

    % Print each row of the service time table
    for i = 1:size(data, 2)
        fprintf('%-15d%-15.2f%-15.2f%-15s\n', data{1, i}, data{2, i}, data{3, i}, data{4, i});
    end
    fprintf('\n');
end
