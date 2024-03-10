import numpy as np

# docs, examples: https://plotoptix.rnd.team
from plotoptix import TkOptiX
from plotoptix.utils import make_color
from plotoptix.materials import m_plastic

def torus(u, v, r, R):
    x = r * np.sin(v)
    y = (R + r * np.cos(v)) * np.sin(u)
    z = (R + r * np.cos(v)) * np.cos(u)
    return np.array([x, y, z], dtype=np.float32)

r = (0, 2*np.pi)
n = 500

i = np.linspace(r[0], r[1], n)

U, V = np.meshgrid(i, i)
S = np.swapaxes(torus(U, V, 3, 5), 0, 2)

rt = TkOptiX(width=1500, height=1800)

rt.set_param(min_accumulation_step=2,
             max_accumulation_frames=500,
             light_shading="Hard")
rt.set_uint("path_seg_range", 6, 15)

rt.setup_material("plastic", m_plastic)

exposure = 0.8; gamma = 2.2
rt.set_float("tonemap_exposure", exposure)
rt.set_float("tonemap_gamma", gamma)
rt.add_postproc("Gamma")

rt.set_background(0)
rt.set_ambient(0.15)

rt.set_surface("surface", S, c=0.94, make_normals=True, mat="plastic")

rt.set_data("plane", geom="Parallelograms",
            pos=[[-100, -9, -100]], u=[200, 0, 0], v=[0, 0, 200],
            c=make_color([0.1, 0.2, 0.3], exposure=exposure, gamma=gamma))

rt.setup_camera("cam1", cam_type="DoF",
                eye=[-50, 5, -15], target=[0, 0, -1], up=[0, 1, 0],
                aperture_radius=0.4, aperture_fract=0.2,
                focal_scale=0.92, fov=32)

rt.setup_light("light1", pos=[-15, 20, 15], color=8, radius=6)

rt.start()
