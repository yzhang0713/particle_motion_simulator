import matplotlib.pyplot as plt
import matplotlib.animation as manimation

x_min = -100.0
x_max = 100.0
y_min = -100.0
y_max = 100.0
n_particle = 1000

FFMpegWriter = manimation.writers['ffmpeg']
metadata = dict(title='Particle Motion Simulator', artist='Matplotlib', comment='Simulate particle motion and collision')
writer = manimation.FFMpegWriter(fps=10, metadata=metadata)

fig = plt.figure()
plt.xlim([x_min, x_max])
plt.ylim([y_min, y_max])

records = []

with open('./cmake-build-debug/domain_record.txt', 'r') as data:
    record = {}
    line = data.readline()
    while line and len(line) > 0:
        if line.startswith('current time'):
            time = float(line.split(':')[1].strip())
            record['time'] = time
            record['particles'] = {}
            line = data.readline()
            while line and not line.startswith('current time'):
                fields = line.split(';')
                particle_id = int(fields[0].split(':')[1].strip())
                x_pos, y_pos = fields[1].split(':')[1].split(',')
                x_pos = float(x_pos[2:]) if not 'n' in x_pos else 0.0
                y_pos = float(y_pos[:-2]) if not 'n' in y_pos else 0.0
                x_vel, y_vel = fields[2].split(':')[1].split(',')
                x_vel = float(x_vel[2:]) if not 'n' in x_vel else 0.0
                y_vel = float(y_vel[:-2]) if not 'n' in y_vel else 0.0
                record['particles'][particle_id] = {'x_pos':x_pos, 'y_pos':y_pos, 'x_vel':x_vel, 'y_vel':y_vel}
                line = data.readline()
            records.append(record)
            record = {}

def get_pos_from_dict(particle_records, n):
    xs = []
    ys = []
    for i in range(n):
        xs.append(particle_records[i]['x_pos'])
        ys.append(particle_records[i]['y_pos'])
    return xs, ys

xs, ys = get_pos_from_dict(records[0]['particles'], n_particle)
scat = plt.scatter(xs, ys, s=1, c='r', alpha=0.5)

with writer.saving(fig, "particle_motion.mp4", 100):
    for i in range(len(records)-1):
        xs, ys = get_pos_from_dict(records[i+1]['particles'], n_particle)
        array = [[xs[j], ys[j]] for j in range(n_particle)]
        scat.set_offsets(array)
        writer.grab_frame()