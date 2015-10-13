% Test input parser

% Preconditions

%% Test 1: If empty string is given returns empty cell
result =tokenizeLine('');
assert(isempty(result));
assert(iscell(result));
%% Test 2: that well formated string is parsed to a cell
parsed_cell =tokenizeLine('ax = 2.5');
expected_cell = {{'ax','2.5'}};
assert(isequal(parsed_cell,expected_cell));
%% Test 3: that wrong formated string is parsed to empty cell
parsed_cell =tokenizeLine('ax = ');
assert(isempty(parsed_cell));
assert(iscell(parsed_cell));
%% Test 4: that multimpe tokes are parsed to nested cell
parsed_cell =tokenizeLine('ax = 2.5, ay = 4');
expected_cell = {{'ax','2.5'},{'ay','4'}};
assert(isequal(parsed_cell,expected_cell));
%% Test 5: that bad formatted token is inogoren in multitoken string
parsed_cell =tokenizeLine('ax = 2.5, bd = , az = 2654');
expected_cell = {{'ax','2.5'},{'az','2654'}};
assert(isequal(parsed_cell,expected_cell));
%% Test 6: that token can ve negative number
parsed_cell =tokenizeLine('ax = -2.5');
expected_cell = {{'ax','-2.5'}};
assert(isequal(parsed_cell,expected_cell));