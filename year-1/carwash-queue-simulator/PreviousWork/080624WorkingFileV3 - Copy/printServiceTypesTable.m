function printServiceTypesTable(serviceTypes_Data)
    % Function to print the service types table
    % Inputs:
    %   serviceTypes_Data - cell array containing service types data
    % Output:
    %   None

    fprintf('%-20s%-15s%-15s%-15s\n', 'Car Wash Service', 'Probability', 'CDF', 'Range');
    
    % Print each row of the service types table
    for i = 1:size(serviceTypes_Data, 2)
        fprintf('%-20s%-15.2f%-15.2f%-15s\n', serviceTypes_Data{1, i}, serviceTypes_Data{2, i}, serviceTypes_Data{3, i}, serviceTypes_Data{4, i});
    end
    fprintf('\n');
end
