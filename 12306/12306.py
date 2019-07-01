import datetime
import json
import os
import sys
from time import sleep

import requests

if len(sys.argv) > 1:
    name = f"_{sys.argv[1]}"
else:
    name = "_0"

try:
    finished_file = open(f"finished{name}.json", "r+")
    finish_list = json.load(finished_file)
except (json.JSONDecodeError, FileNotFoundError) as e:
    finish_list = []

if __name__ == '__main__':
    stations = dict()
    with open("stations.json") as stations_file:
        station = json.load(stations_file)
        for s in station:
            stations[s["name"]] = s["tel_code"]

    session = requests.Session()
    session.headers = {
        "User-Agent": "Mozilla/5.0 (Linux; Android 8.0.0; SM-G960F Build/R16NW) AppleWebKit/537.36 (KHTML, "
                      "like Gecko) Chrome/62.0.3202.84 Mobile Safari/537.36"
    }

    if not os.path.exists(f"./trains{name}"):
        os.mkdir(f"./trains{name}")

    with open(f"original/trains{name}.json") as trains_file:
        train = json.load(trains_file)

    type_map = {
        "O": "二等座",
        "A2": "软座",
        "A1": "硬座",
        "WZ": "无座"
    }
    while True:
        t = None
        try:
            finished = 0
            for t in train:
                valid = True
                if [t["id"], t["week"]] in finish_list:
                    finished += 1
                    print(f"{t['id']} train on {t['week']} finished. rate: {finished / len(train)}")
                    continue
                train_infos = []
                try:
                    request_url = f"https://kyfw.12306.cn/otn/czxx/queryByTrainNo?train_no={t['train_no']}" \
                                  f"&from_station_telecode={stations[t['from']]}&to_station_telecode={stations[t['to']]}" \
                                  f"&depart_date={t['time']}"
                except KeyError:
                    finish_list.append([t['id'], t["week"]])
                    print(f"{t['id']} train skipped, reason: station not found.")
                    continue
                sleep(0.5)
                response = session.get(request_url).json()
                info1 = response["data"]["data"]
                date = datetime.date.fromisoformat(t['time'])
                while datetime.datetime.combine(date=date, time=datetime.time.fromisoformat(
                        info1[0]['start_time'])) < datetime.datetime.now():
                    date = (datetime.datetime.combine(date=date, time=datetime.time.fromisoformat(
                        info1[0]['start_time'])) + datetime.timedelta(days=7)).date()
                info = [{
                    'station': info1[0]['station_name'],
                    'arrive_time': datetime.datetime.now(),
                    'start_time': datetime.datetime.combine(date=date,
                                                            time=datetime.time.fromisoformat(info1[0]['start_time']))
                }]
                for i in range(1, len(info1) - 1):
                    from_time = datetime.datetime.combine(date=date,
                                                          time=datetime.time.fromisoformat(info1[i - 1]['start_time']))
                    to_time = datetime.datetime.combine(date=date,
                                                        time=datetime.time.fromisoformat(info1[i]['arrive_time']))
                    if to_time < from_time:
                        to_time += datetime.timedelta(days=1)
                        date = to_time.date()
                    info.append({
                        'station': info1[i]['station_name'],
                        'arrive_time': to_time,
                        'start_time': datetime.datetime.combine(date=date, time=datetime.time.fromisoformat(
                            info1[i]['start_time']))
                    })
                from_time = datetime.datetime.combine(date=date, time=datetime.time.fromisoformat(
                    info1[len(info1) - 2]['start_time']))
                to_time = datetime.datetime.combine(date=date, time=datetime.time.fromisoformat(
                    info1[len(info1) - 1]['arrive_time']))
                if to_time < from_time:
                    to_time += datetime.timedelta(days=1)
                    date = to_time.date()
                info.append({
                    'station': info1[len(info1) - 1]['station_name'],
                    'arrive_time': to_time,
                    'start_time': datetime.datetime.now()
                })
                for i in range(0, len(info) - 1):
                    for j in range(i + 1, len(info)):
                        from_time = info[i]['start_time']
                        to_time = info[j]['arrive_time']
                        from_station = info[i]['station']
                        to_station = info[j]['station']
                        station_infos = []
                        found = None
                        for response in requests.get(
                                f"https://kyfw.12306.cn/otn/leftTicket/query?leftTicketDTO.train_date="
                                f"{from_time.date()}&leftTicketDTO.from_station={stations[from_station]}"
                                f"&leftTicketDTO.to_station={stations[to_station]}"
                                f"&purpose_codes=ADULT").json()["data"]["result"]:
                            tmp = response.split('|')
                            station_infos.append({
                                "valid": tmp[0],
                                "from_station": tmp[6],
                                "to_station": tmp[7],
                                "train_no": tmp[2],
                                "id": tmp[3],
                                "from_station_no": tmp[16],
                                "to_station_no": tmp[17],
                                "seat_types": tmp[35]
                            })
                        try:
                            found = next(x for x in station_infos if x['id'] == t['id'])
                        except StopIteration:
                            break
                        if found['valid'] == '':
                            valid = False
                            break
                        sleep(0.5)
                        url = f"https://kyfw.12306.cn/otn/leftTicket/queryTicketPrice?train_no={found['train_no']}" \
                            f"&from_station_no={found['from_station_no']}&to_station_no={found['to_station_no']}" \
                            f"&seat_types={found['seat_types']}&train_date={from_time.date()}"
                        response = requests.get(url=url).json()['data']
                        price = dict()
                        sleep(0.5)
                        for tpe, price1 in response.items():
                            try:
                                price[type_map[tpe]] = price1[1:]
                            except KeyError:
                                pass
                        try:
                            temp1 = price[type_map["A1"]]
                            temp2 = price[type_map["A2"]]
                            price.pop(type_map["A2"])
                        except KeyError:
                            pass
                        if type_map["A1"] in price or type_map["A2"] in price or type_map["O"] in price:
                            price.pop(type_map["WZ"])
                        for tpe, p in price.items():
                            rail = {
                                "name": t['id'],
                                "from_station": from_station,
                                "start_time": from_time,
                                "to_station": to_station,
                                'arrive_time': to_time,
                                'used_time': to_time - from_time,
                                'seat_type': tpe,
                                'price': p
                            }
                            train_infos.append(rail)
                            sleep(0.5)
                    if not valid:
                        break
                if valid:
                    with open(f"./trains{name}/{t['id']}_{t['week']}.txt", "w+") as f:
                        for info in train_infos:
                            f.write(
                                f"{info['name']} {info['from_station']} {info['start_time'].strftime('%a')} "
                                f"{info['start_time'].time()} {info['to_station']}"
                                f" {info['arrive_time'].strftime('%a')} "
                                f"{info['arrive_time'].time()} {info['used_time']}"
                                f" {info['seat_type']} {info['price']}\n")
                finished += 1
                finish_list.append([t['id'], t["week"]])
                print(f"{t['id']} train on {t['week']} finished. rate: {finished / len(train)}")
                sleep(1)
        except (KeyboardInterrupt, InterruptedError) as e:
            print("Save and exiting...")
            finished_file = open(f"finished{name}.json", "w")
            json.dump(finish_list, finished_file)
            break
        except:
            print(f"{t['id']} on {t['week']} train failed.")
            finished_file = open(f"finished{name}.json", "w")
            json.dump(finish_list, finished_file)
