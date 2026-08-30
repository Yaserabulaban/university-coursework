function printSimulationTable(simulation_table)
    % Function to print the simulation table
    % Inputs:
    %   simulation_table - cell array containing simulation data
    % Output:
    %   None

    % Validate input
    if ~iscell(simulation_table) || size(simulation_table, 2) ~= 5
        error('Input simulation_table must be a cell array with 5 columns: [n, RN for Inter-arrival time, Inter-arrival time, Arrival time, Service type]');
    end

    % Print table header
    fprintf('%-5s%-30s%-20s%-20s%-20s\n', 'n', 'RN for Inter-arrival', 'Inter-arrival', 'Arrival', 'Service');
    fprintf('%-5s%-30s%-20s%-20s%-20s\n', '', 'time', 'time', 'time', 'type');

    % Print each row of the simulation table
    for i = 1:size(simulation_table, 1)
        fprintf('%-5d%-30d%-20d%-20d%-20s\n', simulation_table{i, 1}, simulation_table{i, 2}, simulation_table{i, 3}, simulation_table{i, 4}, simulation_table{i, 5});
    end
    fprintf('\n');
end
