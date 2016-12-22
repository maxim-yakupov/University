from sklearn.ensemble import RandomForestClassifier
from sklearn.externals import joblib
import numpy as np
import gym
import utils as u
import pickle

dump_path = u.dump_path

flagMakeNewData = input('Make new game data? [0 or 1]') == '1'
flagFit = True#input('Fit model? [0 or 1]') == '1'

if (flagMakeNewData):
    env = gym.make('SpaceInvaders-v0')

    nframes = 5

    records_counter = 0
    for episode in range(100):
        print('---episode ' + str(episode))
        # PREPARE FIRST STEPS
        observation = env.reset()
        n_frames_reward = 0.;
        rewards = np.array([0.]);
        train_data_n_frames = np.hstack((u.to1D(observation), 10))
        # fill first 'nframes' steps
        for step in range(nframes):
            action = env.action_space.sample()
            before_action_observation = observation
            observation, reward, done, info = env.step(action)
            n_frames_reward += reward
            rewards = np.hstack((rewards, reward))
            train_data_n_frames = u.concatNewStep(train_data_n_frames,
                                                  before_action_observation,
                                                  action)
        #input('---Press any key...')
        train_data_n_frames = train_data_n_frames[1:]
        rewards = rewards[1:]
        print('---preparations finished')
        if (episode == 1):
            with open(dump_path + 'dump.dat', 'wb') as dump_out:
                pickle.dump({'0' : [u.to1D(train_data_n_frames), n_frames_reward]}, dump_out)
            records_counter = 1

        # START FITTING
        for step in range(10000 - nframes):
            print('---step ' + str(step))
            if (n_frames_reward > 0.):
                with open(dump_path + 'dump.dat', 'ab') as dump_out:
                    pickle.dump({str(records_counter) : [u.to1D(train_data_n_frames), n_frames_reward]}, dump_out)
                    records_counter = records_counter + 1

            # forget the oldest
            train_data_n_frames = train_data_n_frames[1:]
            n_frames_reward -= rewards[0]
            rewards = rewards[1:]
            
            action = env.action_space.sample()
            before_action_observation = observation

            observation, reward, done, info = env.step(action)
            print('\naction: (' + str(action) + ') reward: ' + str(reward))
            n_frames_reward += reward
            rewards = np.hstack((rewards, reward))
            
            train_data_n_frames = u.concatNewStep(train_data_n_frames,
                                                  before_action_observation,
                                                  action)
            if done:
                print("---Episode finished after {} timesteps".format(step+1))
                break

if (flagFit):
    from sklearn.linear_model import SGDRegressor

    algo = SGDRegressor(loss='huber', alpha=0.1, learning_rate='optimal')

    from sklearn import preprocessing
    
    print('Start fit')
    with open(dump_path + 'dump.dat', 'rb') as dump_in:
        counter = 10000
        while True and counter > 0:
            try:
                counter = counter - 1
                data_new = pickle.load(dump_in).popitem()[1]
                algo.partial_fit(preprocessing.normalize([data_new[0]]), [data_new[1]])
                print(data_new[1])
            except EOFError:
                break
        joblib.dump(algo, dump_path + 'pretrained.pkl')
    print('Fit ended')
