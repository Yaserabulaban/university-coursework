function ranges = getRanges(probabilities)
    % Function to generate ranges based on probabilities
    % Inputs:
    %   probabilities - array of probabilities
    % Output:
    %   ranges - cell array of ranges in string format

    cumulative_prob = cumsum(probabilities);
    ranges = cell(1, length(probabilities));
    lower_bound = 1;

    for i = 1:length(probabilities)
        if probabilities(i) == 0
            ranges{i} = '0 - 0';
        else
            upper_bound = round(cumulative_prob(i) * 100);
            if i == length(probabilities)
                upper_bound = 100; % Ensure the last range ends at 100
            end
            ranges{i} = sprintf('%d - %d', lower_bound, upper_bound);
            lower_bound = upper_bound;
        end
    end
end
