def readParseData(file_name):
    '''
    Given a file name, the function returns a list of competitors.
    Arguments:
        file_name: the input file name. Assume that the input file is in the directory of this script.
    Return value:
        A list of competitors, such that every record is a dictionary, in the following format:
            {'competition name': competition_name, 'competition type': competition_type,
                'competitor id': competitor_id, 'competitor country': competitor_country,
                'result': result}
    '''
    competitors_in_competitions = []
    file = open(file_name, 'r')
    lines = file.readlines()
    competitors = []
    for line in sorted(lines, key=lambda i: i.replace('\n', '').split(' ')[0] == 'competitor', reverse=True):
        line = line.replace('\n', '').split(' ')
        if(line[0] == 'competitor'):
            competitor = {
                'competitor country': line[2],
                'competitor id': int(line[1]),
                'competition name': '',
                'competition type': '',
                'result': -1
            }
            competitors.append(competitor)
        elif(line[0] == 'competition'):
            # Check if we have the current competitor without an assigned competition.
            id = int(line[2])
            exists = False
            for competitor in competitors:
                if(competitor['competitor id'] == id):
                    exists = True
                    new_entry = competitor.copy()
                    new_entry['competition name'] = line[1]
                    new_entry['competition type'] = line[3]
                    new_entry['result'] = int(line[4])
                    competitors_in_competitions.append(new_entry)
                    break
                # Create a new competitor with all the info we need.
                # * TODO Part A, Task 3.4
    return competitors_in_competitions


def printCompetitor(competitor):
    '''
    Given the data of a competitor, the function prints it in a specific format.
    Arguments:
        competitor: {'competition name': competition_name, 'competition type': competition_type,
                        'competitor id': competitor_id, 'competitor country': competitor_country,
                        'result': result}
    '''
    competition_name = competitor['competition name']
    competition_type = competitor['competition type']
    competitor_id = competitor['competitor id']
    competitor_country = competitor['competitor country']
    result = competitor['result']

    # Updated. Safety check for the type of result
    assert(isinstance(result, int))

    print(f'Competitor {competitor_id} from {competitor_country} participated in {competition_name} ({competition_type}) and scored {result}')


def printCompetitionResults(competition_name, winning_gold_country, winning_silver_country, winning_bronze_country):
    '''
    Given a competition name and its champs countries, the function prints the winning countries
        in that competition in a specific format.
    Arguments:
        competition_name: the competition name
        winning_gold_country, winning_silver_country, winning_bronze_country: the champs countries
    '''
    undef_country = 'undef_country'
    countries = [country for country in [winning_gold_country,
                                         winning_silver_country, winning_bronze_country] if country != undef_country]
    print(
        f'The winning competitors in {competition_name} are from: {countries}')


def key_sort_competitor(competitor):
    '''
    A helper function that creates a special key for sorting competitors.
    Arguments:
        competitor: a dictionary contains the data of a competitor in the following format:
                    {'competition name': competition_name, 'competition type': competition_type,
                        'competitor id': competitor_id, 'competitor country': competitor_country,
                        'result': result}
    '''
    competition_name = competitor['competition name']
    result = competitor['result']
    return (competition_name, result)


def calcCompetitionsResults(competitors_in_competitions):
    '''
    Given the data of the competitors, the function returns the champs countries for each competition.
    Arguments:
        competitors_in_competitions: A list that contains the data of the competitors
                                    (see readParseData return value for more info)
    Retuen value:
        A list of competitions and their champs (list of lists). 
        Every record in the list contains the competition name and the champs, in the following format:
        [competition_name, winning_gold_country, winning_silver_country, winning_bronze_country]
    '''

    competitions_champs = []
    completed = []
    # Go through the competitions according to names.
    for competition in sorted(competitors_in_competitions, key=lambda i: i['competition name']):
        name = competition['competition name']
        # Check if we already announced results for this competition.
        if(name in completed):
            continue
        comp_type = competition['competition type']
        # Get the relevant list of competitors
        competitors = [
            comp for comp in competitors_in_competitions if comp['competition name'] == name]
        # Sort the competitors according to the competition type and the result
        if(comp_type == 'untimed'):
            competitors = sorted(competitors,
                                 key=lambda i: i['result'], reverse=True)
        else:
            competitors = sorted(competitors,
                                 key=lambda i: i['result'])
        # We got the competitors for this specific competition, sorted according to the proper results.
        # Now we need to assign the winners to each medal, and to make sure there's no illegal entries.
        disqualification = []
        winners_id = []
        winners = []
        # Go through the competitors for this competition
        for competitor in competitors:
            id = competitor['competitor id']
            country = competitor['competitor country']
            # Check if the current ID is disqualified.
            if(id in disqualification):
                continue
            # Check if the current ID is already in the winners list for this competition
            elif(id in winners_id):
                # Disqualify the current ID, duplicate entries int this competition.
                disqualification.append(id)
                index = winners_id.index(id)
                winners_id.remove(id)
                winners.pop(index)
            # Legal entry. Add to the winners.
            else:
                winners.append(country)
                winners_id.append(id)
        # Use the first 3.
        final = [name]
        # Are there no winners? If so, continue, do not add this to the competition champs.
        if(len(winners) == 0):
            continue
        # Add the first 3 winners we have.
        final.extend(winners[0:3])
        # Check if we have enough winners in the array. If not, add undef_country until we have enough.
        while(len(final)<4):
            final.append('undef_country')
        # Add the final list of winners to the competition champs
        competitions_champs.append(final)
        # Add the name of the competition into the list of completed competitions
        completed.append(name)

        # Go along the competitors and add them.
    return competitions_champs


def partA(file_name='input.txt', allow_prints=True):
    # read and parse the input file
    competitors_in_competitions = readParseData(file_name)
    if allow_prints:
        # competitors_in_competitions are sorted by competition_name (string) and then by result (int)
        for competitor in sorted(competitors_in_competitions, key=key_sort_competitor):
            printCompetitor(competitor)

    # calculate competition results
    competitions_results = calcCompetitionsResults(competitors_in_competitions)
    if allow_prints:
        for competition_result_single in sorted(competitions_results):
            printCompetitionResults(*competition_result_single)

    return competitions_results


def partB(file_name='input.txt'):
    import Olympics
    competitions_results = partA(file_name, allow_prints=False)
    o = Olympics.OlympicsCreate()
    for competition in competitions_results:
        Olympics.OlympicsUpdateCompetitionResults(
            o, str(competition[1]), str(competition[2]), str(competition[3]))
    Olympics.OlympicsWinningCountry(o)
    Olympics.OlympicsDestroy(o)


if __name__ == "__main__":
    '''
    The main part of the script.
    __main__ is the name of the scope in which top-level code executes.

    To run only a single part, comment the line below which correspondes to the part you don't want to run.
    '''
    file_name = 'input.txt'

    partA(file_name)
    partB(file_name)
