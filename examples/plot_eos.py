import numpy as np
import matplotlib.pyplot as plt
import fdlo

theta_arr = np.geomspace(1.0e-2, 1.0e2, 100)
eta_e = 1.0

n_em = [fdlo.n_eminus(theta, eta_e)[0] for theta in theta_arr]
P_em = [fdlo.P_eminus(theta, eta_e)[0] for theta in theta_arr]
U_em = [fdlo.U_eminus(theta, eta_e)[0] for theta in theta_arr]

n_ep = [fdlo.n_eplus(theta, eta_e)[0] for theta in theta_arr]
P_ep = [fdlo.P_eplus(theta, eta_e)[0] for theta in theta_arr]
U_ep = [fdlo.U_eplus(theta, eta_e)[0] for theta in theta_arr]

fig, ax = plt.subplots(2, 1)
ax[0].plot(theta_arr, n_em, label=r'$n_{e^-}$')
ax[0].plot(theta_arr, P_em, label=r'$P_{e^-}$')
ax[0].plot(theta_arr, U_em, label=r'$n_{e^-}$')

ax[1].plot(theta_arr, n_ep, label=r'$n_{e^+}$')
ax[1].plot(theta_arr, P_ep, label=r'$P_{e^+}$')
ax[1].plot(theta_arr, U_ep, label=r'$n_{e^+}$')

ax[0].legend()
ax[1].legend()

ax[0].set(xscale='log', yscale='log', xlabel=r'$\theta_e$')
ax[1].set(xscale='log', yscale='log', xlabel=r'$\theta_e$')

fig.suptitle(r'$\eta_e = 1$')
fig.tight_layout()

figname = "electron_eos.png"
print("Saving", figname)
fig.savefig(figname)

plt.show()
