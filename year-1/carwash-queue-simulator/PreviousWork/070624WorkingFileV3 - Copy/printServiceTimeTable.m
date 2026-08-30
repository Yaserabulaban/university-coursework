function printServiceTimeTable(washBayName, data)
    fprintf('%s:\n', washBayName);
    fprintf('%-15s%-15s%-15s%-15s\n', 'Service Time', 'Probability', 'CDF', 'Range');
    
    % Debug: Check data content
    disp('Debug: Checking data content');
    disp(data);

    for i = 1:size(data, 2)
        fprintf('%-15d%-15.2f%-15.2f%-15s\n', data{1, i}, data{2, i}, data{3, i}, data{4, i});
    end
    fprintf('\n');
end
