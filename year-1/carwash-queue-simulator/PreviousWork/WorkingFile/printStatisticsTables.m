function printStatisticsTables(statistics, car_Interval)
    % Function to print the statistics tables for each wash bay
    for j = 1:3
        fprintf('\n\n');
        fprintf('========================= W A S H   B A Y   %d =========================\n', j);
        fprintf('%-4s %-12s %-11s %-14s %-18s %-16s %-12s %-21s %-10s\n', ...
            'n', 'RN for', 'Arrival', 'Service', 'Time service', 'Time service', 'Waiting', 'Time spends in', 'Service');
        fprintf('%-4s %-12s %-11s %-14s %-18s %-16s %-12s %-21s %-10s\n', ...
            '', 'service time', 'time', 'time', 'begins', 'ends', 'time', 'the system', 'Type');
        
        % Check if the statistics cell array has data for the current wash bay
        if isempty(statistics{j})
            fprintf('No data for Wash Bay %d\n', j);
            continue;
        end
        
        try
            for i = 1:size(statistics{j}, 1)
                if i > length(car_Interval)
                    fprintf('Error: car_Interval index out of range. i = %d, length(car_Interval) = %d\n', i, length(car_Interval));
                else
                    fprintf('%-4d %-12d %-11d %-14d %-18d %-16d %-12d %-21d %-10s\n', ...
                        statistics{j}{i, 1}, statistics{j}{i, 2}, car_Interval(statistics{j}{i, 1}), statistics{j}{i, 4}, ...
                        statistics{j}{i, 5}, statistics{j}{i, 6}, statistics{j}{i, 7}, ...
                        statistics{j}{i, 8}, statistics{j}{i, 3});
                end
            end
        catch ME
            fprintf('Error at wash bay %d, car %d: %s\n', j, i, ME.message);
        end
        
        fprintf('Total cars served by WashBay %d: %d\n', j, size(statistics{j}, 1));
        fprintf('\n');
    end
end
