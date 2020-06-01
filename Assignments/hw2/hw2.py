def printCompetitor(competitor):
    '''
    Given the data of a competitor, the function prints it in a specific format.
    Arguments:
        competitor: {'competition name': competition_name, 'competition type': competition_type,
                        'competitor id': competitor_id, 'competitor country': competitor_country,
                        'result': result}
    '''
    file = open('out.txt', 'a')
    competition_name = competitor['competition name']
    competition_type = competitor['competition type']
    competitor_id = competitor['competitor id']
    competitor_country = competitor['competitor country']
    result = competitor['result']

    # Updated. Safety check for the type of result
    assert(isinstance(result, int))

    print(f'Competitor {competitor_id} from {competitor_country} participated in {competition_name} ({competition_type}) and scored {result}')
    file.write(
        f'Competitor {competitor_id} from {competitor_country} participated in {competition_name} ({competition_type}) and scored {result}\n')


def printCompetitionResults(competition_name, winning_gold_country, winning_silver_country, winning_bronze_country):
    '''
    Given a competition name and its champs countries, the function prints the winning countries
        in that competition in a specific format.
    Arguments:
        competition_name: the competition name
        winning_gold_country, winning_silver_country, winning_bronze_country: the champs countries
    '''
    file = open('out.txt', 'a')
    undef_country = 'undef_country'
    countries = [country for country in [winning_gold_country,
                                         winning_silver_country, winning_bronze_country] if country != undef_country]
    print(
        f'The winning competitors in {competition_name} are from: {countries}')
    file.write(
        f'The winning competitors in {competition_name} are from: {countries}' + '\n')


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
    file = open(file_name, "r+")

    lines = file.readlines()
    for line in sorted(lines, key=lambda i: i.split(' ')[0] == 'competitor', reverse = True):
        line = line.split(' ')
        # Check the beginning of each line:
        line[-1] = line[-1].replace('\n', '')
        if(line[0] == 'competitor'):
            # Create competitor
            new_competitor = {
                'competitor id': line[1],
                'competitor country': line[2],
                'competition type': '',
                'competition name': '',
                'result': -1
            }
            # print(f'Added new competitor: {new_competitor}')
            competitors_in_competitions.append(new_competitor)
        elif(line[0] == 'competition'):
            # Create competition (update competitor?)
            id = line[2]
            for competitor in competitors_in_competitions:
                if(competitor['competitor id'] == id):
                    if(competitor['competition name'] != ''):
                        new_competitor = {
                            'competitor id': id,
                            'competitor country': competitor['competitor country'],
                            'competition type': line[3],
                            'competition name': line[1],
                            'result': int(line[4])
                        }
                        # print(f'Added new competition: {new_competitor}')
                        competitors_in_competitions.append(new_competitor)
                    else:
                        competitor['competition name'] = line[1]
                        competitor['competition type'] = line[3]
                        competitor['result'] = int(line[4])
                        # print(f'Updated competitor: {competitor}')
                    break
    # TODO Part A, Task 3.4
    return competitors_in_competitions


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
    elimination = {competitor['competition name']: []
                   for competitor in competitors_in_competitions}
    competitions = {competitor['competition name']: ['undef_country', 'undef_country', 'undef_country']
                    for competitor in sorted(competitors_in_competitions, key=lambda i: i['competition name'])}
    for competitor in sorted(competitors_in_competitions, key=lambda i: i['result'] if(i['competition type'] == 'untimed')
                             else -i['result'], reverse=True):
        # print(f'Current competitor: {competitor}')
        # Get the current competition and country name
        competition = competitor['competition name']
        id = competitor['competitor id']
        country = (competitor['competitor country'], id)
        # Check if already eliminated.
        if(id in elimination[competition]):
            continue
        elif(country in competitions[competition]):
            # Eliminate country.
            elimination[competition].append(id)
            # Remove current entry.
            competitions[competition].remove(country)
            competitions[competition].append('undef_country')
            continue

        for medal in range(3):
            if(competitions[competition][medal] == 'undef_country'):
                competitions[competition][medal] = country
                break

    for name, countries in competitions.items():
        # Check if we have no gold medal
        if(countries[0] == 'undef_country'):
            continue
        else:
            champs = [name]
            for country in countries:
                if(country == 'undef_country'):
                    champs.append('undef_country')
                    continue
                champs.append(country[0])
            competitions_champs.append(champs)
    # TODO Part A, Task 3.5
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
    competitions_results = partA(file_name, allow_prints=False)
    # TODO Part B


if __name__ == "__main__":
    '''
    The main part of the script.
    __main__ is the name of the scope in which top-level code executes.

    To run only a single part, comment the line below which correspondes to the part you don't want to run.
    '''
    file_name = 'tests/in/test6.txt'
    file = open('out.txt', 'a')
    file.truncate(0)
    file.close()

    partA(file_name)
    partB(file_name)
